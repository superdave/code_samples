/*
 *  Game.h
 *  -BLAM-
 *
 *  Created by David Riley on 11/9/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#ifndef GAME_H
#define GAME_H

// All the Lua stuff is straight-up C defines, so declare them that way.
extern "C" {
#include "lua.h"
    //#include "lapi.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include "gl_config.h"

#include "GLContext.h"
#include "Event.h"
#include "Events.h"
#include "World.h"

class Game
{
public:
    /* Game(ctx, events)
     *
     * Initializes the stuff.
     *
     * Parameters:
     *    ctx:    The context to use for rendering.
     *    events: The events queue.
     */
    Game(GLContext *ctx,
         Events    *evt);
    
    /* ~Game()
     *
     * Cleans up after the game.
     */
    virtual ~Game(void);
    
    /* run(file)
     *
     * Runs a Lua file.
     *
     * Parameters:
     *    file: The file to run.
     *
     * Returns: Nothing.
     */
    virtual void run(const char *file);

    /* initOpenGL()
     *
     * Initializes OpenGL to an appropriate state.
     *
     * Parameters: None.
     *
     * Returns: Nothing.
     */
    void initOpenGL(void);
    
    /* updateOpenGL()
     *
     * Updates the OpenGL context when the screen has changed sizes.
     *
     * Parameters: None.
     *
     * Returns: Nothing.
     */
    void updateOpenGL(float width, float height);
    
private:
    /* performOpenGLUpdate()
     *
     * Actually processes the OpenGL update.
     *
     * Paramters: None.
     *
     * Returns: Nothing.
     */
    void performOpenGLUpdate(void);
    
protected:
    
    // The GL context.
    GLContext *m_ctx;
    
    // The events queue.
    Events    *m_events;
    
    // The World.
    World     *m_world;
    
    // The main Lua state.
    lua_State *m_lua;
    
    float      m_width, m_height;
    
    // An indicator that we need updating.
    bool       m_updateGL;
};



#endif // GAME_H
