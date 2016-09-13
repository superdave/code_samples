-- timers.lua

timers = nil

function timers_run(timers, time)
    -- Start by setting our current timer to the first one.
    local cur = timers
    
    -- We don't have any functions to run to start with.
    functions = {}
    
    -- Do we have any to try?
    while cur and cur.time <= time do
        -- We have one to run.
        table.insert(functions, {f = cur.func, c = cur.context})
        
        -- Did this one get deleted?
        if cur then
            -- If not, move to the next one.
            cur = cur.next
        end
    end
    
    -- Our current is the new base.
    return cur, functions
end
    
    
function timers_add(timers, time, func, ctx)
    -- Initialize our base, current and last pointers.
    local base = timers
    local cur  = base
    local last = nil
    
    -- Make our timer table.
    local timer = {time = time, func = func, context = ctx, next = nil}
    
    -- Go through the timers and find our spot.
    while cur ~= nil and cur.time <= time do
        -- Find the next.
        last = cur
        cur = cur.next
        
    end
        
    -- Set our next pointer.
    timer.next = cur
        
    -- Are we at the start?
    if last == nil then
        -- If so, set the base.
        base = timer
    else
        -- If not, link the last pointer.
        last.next = timer
    end
    
    return base, timer
end

    
function timers_remove(timers, timer)
    local base = timers
    local cur = base
    local last = nil
    
    while cur ~= nil and cur ~= timer do
        -- Go to the next one.
        last = cur
        cur = cur.next
    end
    
    -- Did we find one?  If not, bail out.
    if cur == nil then return timers end
    
    -- If we did, was it the first one?
    if last == nil then
        base = cur.next
    else
        last.next = cur.next
    end
    
    return base
end

          
