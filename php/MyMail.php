<?php
/**
*使用socket与smtp服务器通信，进而发送邮件
*@author GerBawn <lingchen410@163.com>
*@version 1.0
*@last modified 2015/07/18
*/
class MyMail{

    /**
    * @var resource socket资源句柄
    */
    private $socket;

    /**
    * @var string 服务器域名
    */
    private $host;

    /**
    * @var int 端口号
    */
    private $port;

    /**
    * @var string 登录用户名
    */
    private $user;

    /**
    * @var string 密码
    */
    private $password;

    /**
    * @var string 上一条命令的返回值
    */
    private $resp;

    /**
    * Constructor.
    *
    * @param string $host 服务器域名，example: smtp.qq.com
    * @param string $user 用户名
    * @param string $pwd 密码
    * @param int port 端口号
    */
    public function __construct($host, $user, $pwd, $port = 25){
        $this->host = $host;
        $this->port = $port;
        $this->user = base64_encode($user);
        $this->password = base64_encode($pwd);
        $this->socket = fsockopen($this->host, $this->port, $errno, $errstr);
        if($this->socket === false){
            exit("Error number: $errno, Error message: $errstr");
        }

        $resp = fread($this->socket, 1024);
        if(strpos($resp, '220') === false){
            exit('server error: '.$resp);
        }
    }


    /**
    * 执行命令
    *
    * @param string $cmd 要执行的命令
    * @param string|int $returnCode 期待的状态码
    * @return bool 成功返回true，失败返回false
    */
    private function doCommand($cmd, $returnCode){
        if(fwrite($this->socket, $cmd) === false){
            return false;
        }else{
            if(!$this->isSuccess($returnCode)){
                return false;
            }
        }
        return true;
    }

    /**
    * 判断操作是否成功
    * 
    * @param string $code 成功时应该返回的状态码
    * @return bool 成功返回true，失败返回false
    * @throw expcetion 失败抛出异常
    */
    private function isSuccess($code){
        $this->resp = fread($this->socket, 1024);
        if(strpos($this->resp, (string)$code) === false){
            echo $this->resp, PHP_EOL;
            throw new Exception($this->resp);
            return false;
        }
        return true;
    }

    /**
    *判断是不是合法的邮件地址
    *
    * @param string $email 邮件地址
    * @return bool 成功返回true，失败返回false
    */
    private function isEmail($email){
        $pattern = '/^[^_]\w+@\w+\.\w*[^_]$/';
        if(preg_match($pattern, $email)){
            return true;
        }
        return false;
    }

    /**
    * 发送邮件
    *
    * @param string $from 发件人
    * @param string $to 收件人
    * @param string $subject 邮件主题
    * @param string $body 邮件内容
    * @return bool 成功返回true，失败返回false
    */
    public function send($from, $to, $subject, $body){
        if(!$this->isEmail($from) || !$this->isEmail($to)){
            echo 'Please enter valid email.', PHP_EOL;
            return false;
        }
        if(empty($subject) || empty($body)){
            echo 'Subject and Body can not be empty.', PHP_EOL;
            return false;
        }
        //拼接邮件内容
        $detail = "From: $from\r\n";
        $detail .= "To: $to\r\n";
        $detail .= "Subject: $subject\r\n";
        $detail .= "content-type: text/html\r\n";
        $detail .= "charset=utf-8\r\n\r\n";
        $detail .= $body;

        try{
            $this->doCommand("HELO gerbawn\r\n", 250);
            $this->doCommand("AUTH LOGIN\r\n", 334);
            $this->doCommand($this->user."\r\n", 334);
            $this->doCommand($this->password."\r\n", 235);
            $this->doCommand("MAIL FROM:<$from>\r\n", 250);
            $this->doCommand("RCPT TO:<$to>\r\n", 250);
            $this->doCommand("DATA\r\n", 354);
            $this->doCommand($detail."\r\n.\r\n", 250);
        }catch(Exception $e){
            $this->doCommand("QUIT\r\n", 221);
            return false;
        }
        return true;
    }
}