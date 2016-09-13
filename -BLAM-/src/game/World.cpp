/*
 *  World.cpp
 *  -BLAM-
 *
 *  Created by David Riley on 11/7/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#include <list>

#include "World.h"

/* Forward declaration of our Lua initialization. */
static void lua_init_World(lua_State *L, World *w);

/* World(L)
 *
 * Initializes a World with a given Lua state.
 *
 * Parameters:
 *    L: The Lua state to initialize.
 */
World::World(lua_State *L)
{
    // Init our Lua presence.
    lua_init_World(L, this);
}

/* ~World()
 *
 * Cleans up a World after use.
 */
World::~World(void)
{
    // Go through and release.
    for(std::list<Drawable *>::iterator i = m_drawlist.begin();
        i != m_drawlist.end();
        i++)
    {
        (*i)->release();
    }
}

/* addDrawable(obj)
 *
 * Adds a Drawable to the draw list.  The Drawable is retained.
 *
 * Parameter:
 *    obj: The Drawable to draw in future draw passes.
 *
 * Returns: Nothing.
 */
void World::addDrawable(Drawable *obj)
{
    // Drop that drawable in the list.
    m_drawlist.push_back(obj);
    
    obj->retain();
}

/* draw()
 *
 * Draws all the visible objects in the draw list.
 *
 * Parameters: None.
 *
 * Returns: Nothing.
 */
void World::draw(void)
{
    // Go through the drawlist.
    for(std::list<Drawable *>::iterator i = m_drawlist.begin();
        i != m_drawlist.end();
        i++)
    {
        Drawable *d = *i;
        
        // Is it visible?  If so, draw it.
        if(d->isVisible()) d->draw();
    }
}

#pragma mark -
#pragma mark Lua Interface

LUA_BRIDGE_FUNC(world, add_drawable)
{
    World *w = (World *)lua_touserdata(L, lua_upvalueindex(2));
    
    Drawable *d = (Drawable *)lua_touserdata(L, 1);
    
    w->addDrawable(d);
    
    return 0;
}

static luaL_Reg world_metas[] =
{
{NULL, NULL}
};

static luaL_Reg world_methods[] =
{
LUA_BRIDGE_ENTRY(world, add_drawable),
{NULL, NULL}
};

static void lua_init_World(lua_State *L, World *w)
{
    // Start by pushing the World as a light userdata.
    LuaBridgeItem world_upvalues[] = 
    {
        LUA_BRIDGE_ITEM(LUA_BRIDGE_USERDATA, w),
        LUA_BRIDGE_ITEM_END
    };
    
    lua_bridge_export_lib(L,
                          "World",
                          world_methods,
                          world_metas,
                          world_upvalues,
                          "World library");

}


