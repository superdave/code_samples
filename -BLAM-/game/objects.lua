-- objects.lua

Object = {

moveto = function(self, x, y)
    for c in self.children do c:moveto(x, y) end
end,

move = function(self, x, y)
    for c in self.children do c:moveto(x, y) end
end,

hide = function(self)
    for c in self.children do c:hide() end
end,
    
    
show = function(self)
    for c in self.children do c:show() end
end

}
