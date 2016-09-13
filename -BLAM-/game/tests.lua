-- tests.lua

function test_loc(x, y)
    return (64 * x + center.x), (64 * y + center.y)
end

tests = {}

tests[1] = {first = {{sprite = jet, x = 1, y = 0}},
            second = {{sprite = jet, x = 1, y = 0}}}
tests[1].same = true

tests[2] = {first = {{sprite = hover, x = 0, y = 1}},
            second = {{sprite = hover, x = 0, y = 0}}}
tests[2].same = false

