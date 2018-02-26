<?php

class RateLimiter
{
    private $limit;
    private $timeout;
    private $key;
    private $redis;

    public function __construct($limit, $timeout, $key)
    {
        $this->limit = $limit;
        $this->timeout = $timeout;
        $this->key = $key;

        $this->redis = new Redis();
        $this->redis->connect('127.0.0.1', 6379, 10);
    }

    public function getToken(): bool
    {
        if (!$this->updateToken()) {
            return false;
        }

        return $this->redis->evalSha('c671ca8d9617bb0cd2eb7171b7d973437d1e79a2', [$this->key], 1) > 0;
    }

    private function updateToken()
    {
        return $this->redis->evalSha(
            'cc6b0c72201a39404f049278afc8ec362dc4343e',
            [
                $this->key,
                $this->limit,
                $this->timeout,
                microtime(true),
            ],
            1
        );
    }
}