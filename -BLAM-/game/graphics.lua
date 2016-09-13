-- graphics.lua

print "Loading graphics..."

jet = Sprite.new("Jet1t.png")
jet:setorigin(0, 0)
World.add_drawable(jet)

hover = Sprite.new("HoverJet2t.png")
hover:setorigin(2, 0)
World.add_drawable(hover)

cursor = Sprite.new("cursor.png")
cursor:setorigin(0, 15)
cursor:show()
World.add_drawable(cursor)

query = Sprite.new("query.png")
query:setorigin(128, 128)
query:moveto(center.x, center.y)
World.add_drawable(query)

World.sprites = {jet = jet, hover = hover, query = query}

World.objects = {cursor}

