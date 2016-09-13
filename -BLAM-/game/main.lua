print "Hello there."

print "Loading functions..."

dofile("timers.lua")
dofile("events.lua")
dofile("objects.lua")

center = {x = SCREEN_WIDTH / 2,
          y = SCREEN_HEIGHT / 2}

dofile("graphics.lua")

dofile("psych_test.lua")

grid = Grid.new(4, 4, 64, 64)
grid:moveto(center.x, center.y)

done = false

test_context = {}

function main(time, delta)
    timers, timer_funcs = timers_run(timers, time)
    
    if timer_funcs then
        for i,f in ipairs(timer_funcs) do
            func = f.f
            func(time, f.c)
        end
    end
    
    local tests_done = update_tests(time, grid, tests, test_context)
    
    if tests_done then
        for i, t in ipairs(tests) do
            print(string.format("Test %d: Time = %f, Correct = ",
                                i,
                                t.result.time),     
                  t.result.correct)
        end
    end
    
    return done or tests_done
    
end
    