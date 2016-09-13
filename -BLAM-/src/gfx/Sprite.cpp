/*
 *  Sprite.cpp
 *  -BLAM-
 *
 *  Created by David Riley on 11/2/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#include <stdio.h>
#include <string.h>

#include "Sprite.h"

#include "util.h"

#include "lua_bridge.h"
#include "lua.h"
#include "lualib.h"

#define SPRITE_VERSION_MAJOR 0
#define SPRITE_VERSION_MINOR 1
#define SPRITE_VERSION_REV   0

/* Sprite()
 *
 * Creates a new Sprite with a single texture.
 *
 * Parameters:
 *    tex:    The texture to assign to the sprite.
 *    coords: An array of 4 texture coordinates indicating the texture coords
 *            of the sprite within the texture.  If NULL, uses the corners.
 */
Sprite::Sprite(Texture          *tex,
               const Coordinate &depth,
               const Rect2D     *texCoords,
               const Rect2D     *corners,
               const Point2D    &offset)
: Drawable(Point2D(0,0), offset, depth), m_tex(tex)
{
    Rect2D texRect(0, 0, tex->getWidth(), tex->getHeight());
    
    
    // Fill in the texture and rectangle coordinates, if supplied.
    if(texCoords == NULL) texCoords = &texRect;
    if(corners   == NULL) corners   = &texRect;
    
    // Get the points.
    Point2D texCoordPts[4] = {texCoords->pos, texCoords->pos, texCoords->pos, texCoords->pos};
    texCoordPts[2] += texCoords->size;
    texCoordPts[1].x += texCoords->size.x;
    texCoordPts[3].y += texCoords->size.y;
    
    Point2D cornerPts[4] = {corners->pos};
    cornerPts[2] += corners->size;
    cornerPts[1].x += corners->size.x;
    cornerPts[3].y += corners->size.y;
    
    // Copy our corners rectangle into our bounds.
    m_bounds = *corners;
    
    // Allocate the array.
    Graphics_Point coords[4];
    
    // Fill it.
    for(int i = 0; i < 4; i++)
    {
        coords[i] = Graphics_Point(texCoordPts[i], cornerPts[i]);
    }
    
    // Create a VBO with the data.
    m_vbo = new VBO(coords, NULL, 4, 0, GL_QUADS);
    
    m_tex->retain();
}
    

/* Sprite(Sprite)
 *
 * Does a shallow copy, retaining the Texture again.  The new sprite is,
 * however, hidden.
 *
 * Parameters:
 *    src: The source Sprite to copy from.
 */
Sprite::Sprite(const Sprite &src)
: Drawable(src), m_vbo(src.m_vbo)
{
    m_tex = src.m_tex;
    
    m_tex->retain();
    m_vbo->retain();
        
    m_pos = src.m_pos;
    m_theta = src.m_theta;
}

/* ~Sprite()
 *
 * Cleans up after a sprite is done, dereferencing any referenced textures
 * and coordinate arrays.
 */
Sprite::~Sprite(void)
{
    m_tex->release();
    m_vbo->release();
}

/* show()
 *
 * Causes sprite to be drawn when the draw() method is called.
 *
 * Parameters: None.
 *
 * Returns: Nothing.
 */
void Sprite::show(void)
{
    m_visible = true;
}

/* hide()
 *
 * Causes sprite to not be drawn when the draw() method is called.
 *
 * Parameters: None.
 *
 * Returns: Nothing.
 */
void Sprite::hide(void)
{
    m_visible = false;
}

/* setTexture(tex)
 *
 * Sets the sprite's texture to a specific one.
 *
 * Parameters:
 *    tex: The texture to use.
 *
 * Returns: Nothing.
 */
void Sprite::setTexture(Texture *tex)
{
    m_tex->release();
    
    m_tex = tex;
    
    m_tex->retain();
}

/* draw()
 *
 * Draws the object.
 *
 * Parameters: None.
 *
 * Returns: Nothing.
 */
void Sprite::draw(void)
{
    // Bind the texture.
    m_tex->bind();
    
    // Push the matrix.
    glPushMatrix();
    
    // Move.
    Point2D pt = m_pos - m_origin;
    glTranslatef(pt.x, pt.y, m_depth);

    // Rotate.
    glRotatef(m_theta, 0, 0, 1.0);
    
    // Draw.
    m_vbo->draw();

    // Pop the matrix.
    glPopMatrix();
}




#pragma mark -
#pragma mark Lua Interface

static Sprite * checksprite(lua_State *L, int index)
{
	// First, make sure it's a userdata.
	luaL_checktype(L, index, LUA_TUSERDATA);
	
	// Next, make sure it has the right metatable (indicating that it's a
	// sprite).
	lua_getmetatable(L, index);
	if(!lua_equal(L, lua_upvalueindex(1), -1))
		luaL_typerror(L, index, "Sprite");
	
	// Pop the metatable off the stack.
	lua_pop(L, 1);
	
	// Return the Sprite pointer.
	return (Sprite *)lua_touserdata(L, index);
}

static int lua_sprite_new(lua_State *L)
{
	// Get the filename of the new sprite.
	const char *file = lua_tostring(L, 1);
	
    // Make a texture of it.
    Texture *t = new Texture(file);
    
	// Create a full userdata for the sprite.
	Sprite *s = (Sprite *)lua_newuserdata(L, sizeof(Sprite));
    
	// Create a new Sprite with the name using the pointer acquired from the
	// userdata allocation.
	s = new(s) Sprite(t, 0, NULL, NULL);
	
    // We can release the texture now.
    t->release();
    
	// Get the metatable.
	lua_pushvalue(L, lua_upvalueindex(1));
	
	// Store it in the object.
	lua_setmetatable(L, -2);
	
	// Return.
	return 1;
}

static int lua_sprite_copy(lua_State *L)
{
    // Get our source sprite.
	Sprite *src = (Sprite *)check_type(L, 1, "Sprite");
    
	// Create a full userdata for the new sprite.
	Sprite *s = (Sprite *)lua_newuserdata(L, sizeof(Sprite));
    
	// Create a new Sprite copying the current one.
	s = new(s) Sprite(*src);
	
	// Get the metatable.
	lua_pushvalue(L, lua_upvalueindex(1));
	
	// Store it in the object.
	lua_setmetatable(L, -2);
	
	// Return.
	return 1;
}

static int lua_sprite_width(lua_State *L)
{
	// Get the sprite.
	Sprite *s = (Sprite *)check_type(L, 1, "Sprite");
	
	// Push the width.
	lua_pushinteger(L, 0);
	
	// We've got just the one return value.
	return 1;
}

static int lua_sprite_height(lua_State *L)
{
	// Get the sprite.
	Sprite *s = (Sprite *)check_type(L, 1, "Sprite");
	
	// Push the width.
	lua_pushinteger(L, 0);
	
	// We've got just the one return value.
	return 1;
}

static int lua_sprite_setorigin(lua_State *L)
{
	// Get the sprite.
	Sprite *s = (Sprite *)check_type(L, 1, "Sprite");
	
    // Pull the origin.
    Point2D o = Point2D(lua_tonumber(L, 2), lua_tonumber(L, 3));
    
    // Set the offset.
    s->setOrigin(o);

	// No return.
	return 0;
}

static int lua_sprite_delete(lua_State *L)
{
	// Make sure it's a Sprite.
	Sprite *s = (Sprite *)check_type(L, 1, "Sprite");
	
    dprintf("Releasing sprite.\n");
    
	if(s != NULL) s->~Sprite();
	else dprintf("lua_sprite_delete: Tried to delete non-userdata.\n");
	
	return 0;
}

static int lua_sprite_moveto(lua_State *L)
{
    // Get the sprite.
	Sprite *s = (Sprite *)check_type(L, 1, "Sprite");
    
	// Make sure it was good.
	if(s == NULL)
	{
		dprintf("Bad sprite parameter to lua_sprite_draw.\n");
		return 0;
	}
    
	// Get the X and Y coordinates, and the rotation.
	float x = lua_tonumber(L, 2);
	float y = lua_tonumber(L, 3);
	//float rot = lua_tonumber(L, 4);
	
    // Move the sprite.
    s->setPos(Point2D(x, y));
    //s->setRot(rot);
    
    return 0;
}

static int lua_sprite_show(lua_State *L)
{
    // Get the sprite.
	Sprite *s = (Sprite *)check_type(L, 1, "Sprite");
    
	// Make sure it was good.
	if(s == NULL)
	{
		dprintf("Bad sprite parameter to lua_sprite_draw.\n");
		return 0;
	}
    
    s->show();
    
    return 1;
}

static int lua_sprite_hide(lua_State *L)
{
    // Get the sprite.
	Sprite *s = (Sprite *)check_type(L, 1, "Sprite");
    
	// Make sure it was good.
	if(s == NULL)
	{
		dprintf("Bad sprite parameter to lua_sprite_draw.\n");
		return 0;
	}
    
    s->hide();
    
    return 1;
}

static int lua_sprite_move(lua_State *L)
{
    // Get the sprite.
	Sprite *s = (Sprite *)check_type(L, 1, "Sprite");
    
	// Make sure it was good.
	if(s == NULL)
	{
		dprintf("Bad sprite parameter to lua_sprite_draw.\n");
		return 0;
	}
    
	// Get the X and Y coordinates, and the rotation.
	float x = lua_tonumber(L, 2);
	float y = lua_tonumber(L, 3);
	float rot = lua_tonumber(L, 4);
	
    // Move the sprite.
    s->move(Point2D(x, y));
    //s->setRot(rot);
    
    return 0;
}

static int lua_sprite_draw(lua_State *L)
{
	// Get the sprite.
	Sprite *s = (Sprite *)check_type(L, 1, "Sprite");
    
	// Make sure it was good.
	if(s == NULL)
	{
		dprintf("Bad sprite parameter to lua_sprite_draw.\n");
		return 0;
	}
		
	// Get the X and Y coordinates, and the rotation.
	float x = lua_tonumber(L, 2);
	float y = lua_tonumber(L, 3);
	//float rot = lua_tonumber(L, 4);
	
    // Move the sprite.
    s->setPos(Point2D(x, y));
    //s->setRot(rot);
    
	// Draw the sprite.
	s->draw();
	
    printf("Drawing sprite at (%f, %f)\n", x, y);
    
	// We're done.
	return 0;
}

static luaL_Reg sprite_meta[] =
{
{"__gc", lua_sprite_delete},
{NULL, NULL}
};

static luaL_Reg sprite_methods[] =
{
LUA_BRIDGE_ENTRY(sprite, new),
LUA_BRIDGE_ENTRY(sprite, copy),
LUA_BRIDGE_ENTRY(sprite, move),
LUA_BRIDGE_ENTRY(sprite, moveto),
LUA_BRIDGE_ENTRY(sprite, draw),
LUA_BRIDGE_ENTRY(sprite, show),
LUA_BRIDGE_ENTRY(sprite, hide),
LUA_BRIDGE_ENTRY(sprite, setorigin),
LUA_BRIDGE_ENTRY(sprite, width),
LUA_BRIDGE_ENTRY(sprite, height),
{NULL, NULL}
};

LUA_BRIDGE_EXPORT_LIB(BLAM,
                      Sprite,
                      sprite_methods,
                      sprite_meta,
                      NULL,
                      "Sprite library");

/* static lua_init(L)
 *
 * Initializes the Sprite Lua library.
 *
 * Parameters:
 *    L: The Lua context.
 *
 * Returns: Nothing.
 */
void Sprite::lua_init(lua_State *L)
{
    luaopen_BLAM_Sprite(L);
}

