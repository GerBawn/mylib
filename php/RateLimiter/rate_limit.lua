local key = KEYS[1]
local max = tonumber(ARGV[1]) --速率限制
local timeout = tonumber(ARGV[2]) --时间限制，以秒为单位
local now = tonumber(ARGV[3]) --当前时间戳，微秒
local tokenInfo = redis.call('hgetall', key)

if table.maxn(tokenInfo) == 0 then
    redis.call('hmset', key, 'last_refill_time', now, 'remain_num', max)
    return max
else
    local interval = now - tonumber(tokenInfo[2])
    local rate = timeout / max
    local needAddTokens = math.floor(interval / rate)
    if needAddTokens > 1 then
        local currentTokens = math.min(tonumber(tokenInfo[4]) + needAddTokens, max)
        redis.call('hmset', key, 'last_refill_time', now, 'remain_num', currentTokens)
        return currentTokens
    else
        return tokenInfo[4]
    end
end

