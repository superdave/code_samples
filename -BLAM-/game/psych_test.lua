-- psych_test.lua

dofile("tests.lua")

Grid = {
    new = function(width, height, grid_width, grid_height)

        total_width = (width * grid_width)
        total_height = (height * grid_height)
        
        print(total_width, total_height)

        grid = {}
        grid.origin = {x = total_width / 2,
                       y = total_height / 2}
      
        grid.children = {}
        grid.child_origins = {}
        sprite = Sprite.new("square.png")
        sprite:moveto(0, 0)
        
        for x = 0, width - 1 do
            for y = 0, height - 1 do
                xpos = x * grid_width - grid.origin.x
                ypos = y * grid_height - grid.origin.y
                
                s = sprite:copy()
                s:moveto(xpos, ypos)
                table.insert(grid.child_origins, {x = xpos,
                                                  y = ypos})
                table.insert(grid.children, s)
                World.add_drawable(s)
            end
        end
        
        return setmetatable(grid, {__index = Grid})
    end,
    
    show = function(self)
        for k, c in pairs(self.children) do
            c:show()
        end
    end,
    
    hide = function(self)
        for k, c in pairs(self.children) do
            c:hide()
        end
    end,
    
    move = function(self, dx, dy)
        for k, c in pairs(self.children) do
            c:move(dx, dy)
        end
    end,
    
    moveto = function(self, x, y)
        for k, c in ipairs(self.children) do
            c:moveto((x + self.child_origins[k].x),
                     (y + self.child_origins[k].y))
        end
    end,
    
}

setmetatable(Grid, {__index = Grid})

state = "idle"

function update_tests(time, grid, tests, ctx)
    if not ctx.current_index then ctx.current_index = 1 end
    test = tests[ctx.current_index]
    
    local tests_done = false

    if state == "idle" then
        if test == nil then
            tests_done = true
        elseif Events.clicked then
            state = "showing"
            start_grid_timers(time, grid, test)
        end
    elseif state == "shown" then
        print "Done showing!"
        World.sprites.query:show()
        ctx.query_time = time
        state = "querying"
    elseif state == "querying" then
        answer = nil
    
        if(Events.keys[string.byte("y")]) then
            answer = true
        elseif(Events.keys[string.byte("n")]) then
            answer = false
        end
        
        if answer ~= nil then
            correct = (answer == test.same)
            print("Correct:", correct)
            test.result = {correct = correct, time = (time - ctx.query_time)}
            World.sprites.query:hide()
            ctx.current_index = ctx.current_index + 1
            state = "idle"
        end
    end
    
    
    return tests_done
end

function perform_showing(test)
    hidelist = {}
    for i, t in ipairs(test) do
        table.insert(hidelist, t.sprite)
        
        t.sprite:show()
        t.sprite:moveto(test_loc(t.x, t.y))
    end
    
    test.hide = hidelist
end

function perform_hiding(test)
    for i, s in ipairs(test.hide) do s:hide() end
end

function start_grid_timers(time, grid, test)
    context = {grid = grid, first = true, done = false, test = test}
    show_grid(time, context)
end

function show_grid(time, ctx)
    ctx.grid:show()

    if ctx.first then
        perform_showing(ctx.test.first)
    else
        perform_showing(ctx.test.second)
    end
        
    timers = timers_add(timers,
                        time + 1.2,
                        hide_grid,
                        ctx)
                                      
end

function hide_grid(time, ctx)
    print "hiding!"
    print(ctx.first)
    ctx.grid:hide()
    --for i, s in ipairs(World.hideobjects) do s:hide() end
   
    if ctx.first then
        perform_hiding(ctx.test.first)
    else
        perform_hiding(ctx.test.second)
    end
            
    if ctx.first then
        ctx.first = false
        timers = timers_add(timers,
                            time + 2.0,
                            show_grid,
                            ctx)
    else
        ctx.done = true
        state = "shown"
    end
end
