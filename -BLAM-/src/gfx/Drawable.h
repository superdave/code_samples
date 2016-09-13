/*
 *  Drawable.h
 *  -BLAM-
 *
 *  Created by David Riley on 11/7/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Object.h"

#include "geometry.h"

class Drawable : public Object
{
public:
    /* Drawable()
     *
     * Initializes a drawable object, initially hidden.
     *
     * Parameters:
     *    pos:    The initial position of the drawable.
     *    origin: The origin offset of the drawable.
     */
    Drawable(const Point2D    &pos    = Point2D(0,0),
             const Point2D    &origin = Point2D(0,0),
             const Coordinate &depth  = Coordinate(0),
             const float       theta  = 0.0f);
    
    /* ~Drawable()
     *
     * Cleans up after a drawable object.
     */
    virtual ~Drawable(void);
    
    /* setPos()
     *
     * Sets the position of the Drawable.
     *
     * Parameters:
     *    pos: The new position of the Drawable.
     *
     * Returns: Nothing.
     */
    virtual void setPos(const Point2D &pos);
    
    /* getPos()
     *
     * Returns the position of the Drawable.
     *
     * Parameters: None.
     *
     * Returns: A const reference to the sprite's origin's Drawable.
     */
    virtual const Point2D & getPos(void) const;
    
    /* move()
     *
     * Offsets the Drawable's position.
     *
     * Parameters:
     *    offset: The offset to move the object by.
     *
     * Returns: Nothing.
     */
    virtual void move(const Vector2D &offset);

    /* setOrigin()
     *
     * Sets the origin offset of the Drawable.
     *
     * Parameters:
     *    origin: The new origin offset of the Drawable.
     *
     * Returns: Nothing.
     */
    virtual void setOrigin(const Point2D &origin);
    
    /* getOrigin()
     *
     * Gets the origin offset of the Drawable.
     *
     * Parameters: None.
     *
     * Returns: The origin offset of the Drawable.
     */
    virtual const Point2D & setOrigin(void) const;

    /* rotate()
     *
     * Increments the object's theta by a given amount.
     *
     * Parameters:
     *    theta: The amount by which to rotate.
     *
     * Returns: Nothing.
     */
    virtual void rotate(float theta);
    
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
    
    /* isVisible()
     *
     * Predicate to determine if an object is visible.
     *
     * Parameters: None.
     *
     * Returns: A bool indicating whether the object is visible.
     */
    virtual bool isVisible(void) const;
    
    /* draw()
     *
     * Draws the object.
     *
     * Parameters: None.
     *
     * Returns: Nothing.
     */
    virtual void draw(void) = 0;
    
protected:
    
    // Our origin offset.
    Point2D m_origin;
    Point2D m_pos;

    // Our depth and rotation.
    Coordinate m_depth;
    float      m_theta;
    
    // Are we to be drawn?
    bool m_visible;
};

#endif DRAWABLE_H
