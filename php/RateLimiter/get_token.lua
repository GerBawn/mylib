local key = KEYS[1]
local remainTokens = tonumber(redis.call('hget', key, 'remain_num'))
if remainTokens <= 0 then
    return false
else
    redis.call('hset', key, 'remain_num', remainTokens - 1)
    return true
end


