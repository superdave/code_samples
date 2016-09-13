/*
 *  World.h
 *  -BLAM-
 *
 *  Created by David Riley on 11/7/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#ifndef WORLD_H
#define WORLD_H

#include <list>

#include "Drawable.h"
#include "lua_bridge.h"

class World
{
public:
    /* World(L)
     *
     * Initializes a World with a given Lua state.
     *
     * Parameters:
     *    L: The Lua state to initialize.
     */
    World(lua_State *l);
    
    /* ~World()
     *
     * Cleans up a World after use.
     */
    ~World(void);
    
    /* addDrawable(obj)
     *
     * Adds a Drawable to the draw list.  The Drawable is retained.
     *
     * Parameter:
     *    obj: The Drawable to draw in future draw passes.
     *
     * Returns: Nothing.
     */
    void addDrawable(Drawable *obj);
    
    /* draw()
     *
     * Draws all the visible objects in the draw list.
     *
     * Parameters: None.
     *
     * Returns: Nothing.
     */
    void draw(void);
    
protected:
    
    // The list of Drawables we draw.
    std::list<Drawable *> m_drawlist;
};

#endif // WORLD_H
