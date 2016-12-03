<?php

/**
 *一个简单的PHP守护进程类，主进程负责创建子进程，子进程处理具体业务逻辑
 * @author GerBawn <gerbawn@gmail.com>
 * @version 1.0
 * @last modified 2016/12/03
 */
class Daemonize
{

    private $config = [
        'pid_file' => '/opt/php_daemonize.pid',
        'max_child_num' => 5,
        'log_file' => '/tmp/daemon.log',
    ];

    private $childNum = 0;

    private $parentFunc;

    private $childFunc;

    private $stopFunc;

    private $dataSrc;

    private $pidFile;

    public function __construct($parentFunc, $childFunc, $config = [], $dataSrcFunc = '', $stopFunc = '')
    {
        if (php_sapi_name() !== 'cli') {
            exit('这个类只能在命令行模式下运行');
        }
        if (!extension_loaded('pcntl')) {
            exit('请先安装pcntl扩展');
        }
        if (!extension_loaded('posix')) {
            exit('请先安装posix扩展');
        }

        foreach ($config as $key => $value) {
            $this->config[$key] = $config[$key];
        }

        if (function_exists($dataSrcFunc)) {
            $this->dataSrc = $dataSrcFunc();
        }
        if (!function_exists($parentFunc)) {
            exit('请输入父程序需要执行的函数');
        }
        if (!function_exists($childFunc)) {
            exit('请输入子程序需要执行的函数');
        }
        if (!function_exists($stopFunc)) {
            exit('请输入子程序需要执行的函数');
        }

        $this->parentFunc = $parentFunc;
        $this->childFunc = $childFunc;
        $this->stopFunc = $stopFunc;
    }

    public function run($command)
    {
        $command = strtolower($command);
        switch ($command) {
            case 'create':
                $this->daemon();
                $this->signalProcess();

                if (!$this->lock()) {
                    exit('程序已经启动' . PHP_EOL);
                }
                while (true) {
                    pcntl_signal_dispatch();
                    $data = ($this->parentFunc)($this->dataSrc);
                    if ($data) {
                        while ($this->childNum >= $this->config['max_child_num']) {
                            pcntl_signal_dispatch();
                        }
                        //创建子进程执行任务
                        $pid = pcntl_fork();
                        if ($pid === -1) {
                            $this->log('error', 'create child process fail');
                            exit();
                        } elseif ($pid) {
                            $this->childNum++;
                        } else {
                            pcntl_signal(SIGCHLD, SIG_DFL);
                            ($this->childFunc)($data, $this->dataSrc);
                            exit();
                        }
                    }
                }
                break;
            case 'stop':
                if (file_exists($this->config['pid_file'])) {
                    $pid = file_get_contents($this->config['pid_file']);
                    if (posix_kill($pid, SIGTERM)) {
                        unlink($this->config['pid_file']);
                    }
                    if ($this->stopFunc) {
                        ($this->stopFunc)();
                    }
                }
                break;
            default:
                exit('未知命令');
        }
    }

    private function signalProcess()
    {
        pcntl_signal(
            SIGCHLD,
            function () {
                while (pcntl_wait($status, WNOHANG) > 0) {
                    $this->childNum--;
                }
            }
        );
    }

    private function daemon()
    {
        //父进程退出
        $pid = pcntl_fork();
        if ($pid === -1) {
            exit('创建子进程失败');
        } elseif ($pid) {
            exit();
        }

        //使进程脱离终端
        posix_setsid();

        //一级子进程退出，生成守护进程
        $pid = pcntl_fork();
        if ($pid === -1) {
            exit('创建子进程失败');
        } elseif ($pid) {
            exit();
        }
    }

    private function lock()
    {
        //这里必须使用a模式打开，w模式会在打开时清除文件，导致pid丢失
        $this->pidFile = fopen($this->config['pid_file'], 'a');
        if (flock($this->pidFile, LOCK_EX | LOCK_NB)) {
            $pid = posix_getpid();
            ftruncate($this->pidFile, 0);
            fwrite($this->pidFile, $pid);
            fflush($this->pidFile);

            return true;
        }
        return false;
    }

    private function log($type, $msg)
    {
        $msg = strtoupper($type) . ' | ' . date('Y-m-d H:i:s') . ' | ' . $msg . PHP_EOL;
        file_put_contents($this->config['log_file'], $msg, FILE_APPEND);
    }
}
