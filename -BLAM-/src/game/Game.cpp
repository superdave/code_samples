/*
 *  Game.cpp
 *  -BLAM-
 *
 *  Created by David Riley on 11/9/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#include <unistd.h>
#include <sys/param.h>

#include "util.h"
#include "geometry.h"

#include "Game.h"
#include "Exception.h"

#include "Sprite.h"
#include "Texture.h"

/* Game(gamePath, init)
 *
 * Initializes the stuff.
 *
 * Parameters:
 *    ctx: The context to use for rendering.
 */
Game::Game(GLContext *ctx,
           Events    *events)
: m_ctx(ctx), m_events(events), m_updateGL(false)
{
    // Start Lua.
    m_lua = luaL_newstate();
    
    // Check that we have a good value.
	ASSERT_EXCEPTION(m_lua != NULL, LuaException, "No memory");

    // Open the Lua libraries.
    luaL_openlibs(m_lua);
    
    // Open our own Lua libraries.
    Sprite::lua_init(m_lua);
    
    // Change the working directory.
    chdir("game");
}

/* initOpenGL()
 *
 * Initializes OpenGL to an appropriate state.
 *
 * Parameters: None.
 *
 * Returns: Nothing.
 */
void Game::initOpenGL(void)
{
    
    // Always update GL the first time.
    performOpenGLUpdate();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_RECTANGLE_ARB);
    glEnable(GL_BLEND);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
    glClearColor(1, 1, 1, 1);
    glClearDepth(1.0f);
    glFrontFace(GL_CCW);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

/* updateOpenGL()
 *
 * Updates the OpenGL context when the screen has changed sizes.
 *
 * Parameters: None.
 *
 * Returns: Nothing.
 */
void Game::updateOpenGL(float width, float height)
{    
    m_width = width;
    m_height = height;

    m_updateGL = true;
}

/* performOpenGLUpdate()
 *
 * Actually processes the OpenGL update.
 *
 * Paramters: None.
 *
 * Returns: Nothing.
 */
void Game::performOpenGLUpdate(void)
{
    // Lock the context before we do anything.
    m_ctx->lock();
    
    // Do the internal update.
    m_ctx->update();
    
    // Get the width and height.
    int w = m_ctx->getWidth();
    int h = m_ctx->getHeight();
    
    dprintf("Updating OpenGL to: (%d, %d)\n", w, h);
    
    // Set to projection, since we're changing the projection matrix.
    glMatrixMode(GL_PROJECTION);
    
    // Let's start from the beginning (a very good place to start).
    glLoadIdentity();
    
    // Set the matrix.
    gluOrtho2D(0, w, 0, h);
    
    // Now set the viewport.
    glViewport(0, 0, w, h);
    
    // Go back to modelview.
    glMatrixMode(GL_MODELVIEW);
    
    // Set the screen width and height in Lua.
    lua_pushnumber(m_lua, w);
    lua_setglobal(m_lua, "SCREEN_WIDTH");
    
    lua_pushnumber(m_lua, h);
    lua_setglobal(m_lua, "SCREEN_HEIGHT");
    
    // We've updated.  No need to trigger again.
    m_updateGL = false;
    
    // Unlock the context now that we're done.
    m_ctx->unlock();
}    


/* ~Game()
 *
 * Cleans up after the game.
 */
Game::~Game(void)
{
    printf("Closing Game object %p\n", this);
    lua_close(m_lua);
}

/* run(file)
 *
 * Runs a Lua file.
 *
 * Parameters:
 *    file: The file to run.
 *
 * Returns: Nothing.
 */
void Game::run(const char *file)
{
    // Start the world.
    m_world = new World(m_lua);
    
    // Initialize OpenGL.
    this->initOpenGL();
    
    char cwd[MAXPATHLEN + 1];
    getcwd(cwd, MAXPATHLEN);
    printf("cwd: %s\n", cwd);
    
    // Run the script.
	int err = luaL_dofile(m_lua, file);
	
	// If it failed, throw the exception with the last error.
	ASSERT_EXCEPTION(err == 0, LuaException, lua_tostring(m_lua, -1));

    Point2D mouseLoc;
    
    // Get the time.
    double prevTime = get_current_time();
    
    // Just go.
    bool done = false;
    while(!done)
    {
        // Get our time and our deltas.
        double currentTime = get_current_time();
        double deltaTime = currentTime - prevTime;
        prevTime = currentTime;
        
        // Do we need to update OpenGL?
        if(m_updateGL) performOpenGLUpdate();

        // Check for events.
        while(Event *evt = m_events->getEvent())
        {
            lua_run_event(m_lua, evt, currentTime);
            
            evt->release();
        }            

        
        // Perform the update function with the time and delta.
        lua_getglobal(m_lua, "main");
        lua_pushnumber(m_lua, currentTime);
        lua_pushnumber(m_lua, deltaTime);
        int err = lua_pcall(m_lua, 2, 1, 0);
        if(err)
        {
            printf("Lua error: %s\n", lua_tostring(m_lua, -1));
        } else {
            done = lua_toboolean(m_lua, -1);
        }
        
        // Pop off either the error or the return value.
        lua_pop(m_lua, 1);
        
        // Lock our context before we start with the drawing.
        m_ctx->lock();
        
        // Clear the screen and draw.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_world->draw();
        
        // Swap the screen out...
        m_ctx->swap();
        
        // And unlock our context.
        m_ctx->unlock();
    }
}

