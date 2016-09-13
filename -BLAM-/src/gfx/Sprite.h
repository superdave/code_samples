/*
 *  Sprite.h
 *  -BLAM-
 *
 *  Created by David Riley on 11/2/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#ifndef SPRITE_H
#define SPRITE_H

#include <stdio.h>

#include "Object.h"
#include "DataObject.h"

#include "VBO.h"

#include "Drawable.h"

#include "Texture.h"

#include "Geometry.h"

#include "lua_bridge.h"

class Sprite : public Drawable
{
public:
    /* Sprite()
     *
     * Creates a new Sprite with a single texture.
     *
     * Parameters:
     *    tex:    The texture to assign to the sprite.
     *    coords: An array of 4 texture coordinates indicating the texture coords
     *            of the sprite within the texture.  If NULL, uses the corners.
     */
    Sprite(Texture          *tex,
           const Coordinate &depth,
           const Rect2D     *texCoords,
           const Rect2D     *corners,
           const Point2D    &offset = Point2D(0,0));
    
    /* Sprite(Sprite)
     *
     * Does a shallow copy, retaining the Texture again.  The new sprite is,
     * however, hidden.
     *
     * Parameters:
     *    src: The source Sprite to copy from.
     */
    Sprite(const Sprite &src);
    
    /* static lua_init(L)
     *
     * Initializes the Sprite Lua library.
     *
     * Parameters:
     *    L: The Lua context.
     *
     * Returns: Nothing.
     */
    static void lua_init(lua_State *L);
     
    /* ~Sprite()
     *
     * Cleans up after a sprite is done, dereferencing any referenced textures
     * and coordinate arrays.
     */
    virtual ~Sprite(void);
        
    /* show()
     *
     * Causes sprite to be drawn when the draw() method is called.
     *
     * Parameters: None.
     *
     * Returns: Nothing.
     */
    virtual void show(void);
    
    /* hide()
     *
     * Causes sprite to not be drawn when the draw() method is called.
     *
     * Parameters: None.
     *
     * Returns: Nothing.
     */
    virtual void hide(void);
    
    /* draw()
     *
     * Draws the object.
     *
     * Parameters: None.
     *
     * Returns: Nothing.
     */
    virtual void draw(void);

    /* setTexture(tex)
     *
     * Sets the sprite's texture to a specific one.
     *
     * Parameters:
     *    tex: The texture to use.
     *
     * Returns: Nothing.
     */
    void setTexture(Texture *tex);
    
protected:
    
    // The texture we're based on.
    Texture   *m_tex;
    
    // The coordinate array.
    VBO       *m_vbo;
    
    // The bounding rect.
    Rect2D     m_bounds;
    
};

#endif // SPRITE_H
