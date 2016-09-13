-- init.lua

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

