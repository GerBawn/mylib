<?php
/**
 * file MyMemcached.php
 * @auther GerBawn
 * @time 2015/12/11
 */

class MyMemcached{
    private $_memcached;

    public function __construct(){
        if(!class_exists('Memcached')){
            throw new Exception('Memcached extension is uninstalled.');
        }
        $this->_memcached = new Memcached();
    }

    public function get($key){
        if(is_array($key)){
            $result = $this->_memcached->getMulti($key);
        }else{
            $result = $this->_memcached->get($key);
        }
        return $result;
    }

    public function set($key, $value = '', $expiration = 0){
        $argsNum = func_num_args();
        $args = func_get_args();
        if(is_array($key)){
            if($argsNum == 1){
                $result = $this->_memcached->setMulti($args[0]);
            }elseif($argsNum == 2){
                $result = $this->_memcached->setMulti($args[0], $args[1]);
            }else{
                throw new Exception('Too many args');
            }
        }else{
            $result = $this->_memcached->set($key, $value, $expiration);
        }
        return $result;
    }

    public function delete($key){
        if(is_array($key)){
            $result = $this->_memcached->deleteMulti($key);
        }else{
            $result = $this->_memcached->delete($key);
        }
        return $result;
    }

    public function getErrno(){
        return $this->_memcached->getResultCode();
    }

    public function getErrMsg(){
        return $this->_memcached->getResultMessage();
    }
}