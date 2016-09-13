/*
 *  Drawable.cpp
 *  -BLAM-
 *
 *  Created by David Riley on 11/7/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#include "Drawable.h"

#define _USE_MATH_DEFINES
#include <cmath>

/* Drawable()
 *
 * Initializes a drawable object, initially hidden.
 *
 * Parameters:
 *    pos:    The initial position of the drawable.
 *    origin: The origin offset of the drawable.
 */
Drawable::Drawable(const Point2D &pos,
                   const Point2D &origin,
                   const Coordinate &depth,
                   const float       theta)
: m_origin(origin), m_pos(pos), m_visible(false), m_depth(depth), m_theta(theta)
{
    // Nothing here.
}

/* ~Drawable()
 *
 * Cleans up after a drawable object.
 */
Drawable::~Drawable(void)
{
}

/* setPos()
 *
 * Sets the position of the Drawable.
 *
 * Parameters:
 *    pos: The new position of the Drawable.
 *
 * Returns: Nothing.
 */
void Drawable::setPos(const Point2D &pos)
{
    m_pos = pos;
}

/* getPos()
 *
 * Returns the position of the Drawable.
 *
 * Parameters: None.
 *
 * Returns: A const reference to the Drawable's origin's position.
 */
const Point2D & Drawable::getPos(void) const
{
    return m_pos;
}

/* move()
 *
 * Offsets the Drawable's position.
 *
 * Parameters:
 *    offset: The offset to move the object by.
 *
 * Returns: Nothing.
 */
void Drawable::move(const Vector2D &offset)
{
    m_pos += offset;
}

/* setOrigin()
 *
 * Sets the origin offset of the Drawable.
 *
 * Parameters:
 *    origin: The new origin offset of the Drawable.
 *
 * Returns: Nothing.
 */
void Drawable::setOrigin(const Point2D &origin)
{
    m_origin = origin;
}

/* getOrigin()
 *
 * Gets the origin offset of the Drawable.
 *
 * Parameters: None.
 *
 * Returns: The origin offset of the Drawable.
 */
const Point2D & Drawable::setOrigin(void) const
{
    return m_origin;
}


/* rotate()
 *
 * Increments the object's theta by a given amount.
 *
 * Parameters:
 *    theta: The amount by which to rotate.
 *
 * Returns: Nothing.
 */
void Drawable::rotate(float theta) {
    m_theta += theta;
    
    if(m_theta >= 2 * M_PI) m_theta -= (2 * M_PI);
}

/* show()
 *
 * Causes sprite to be drawn when the draw() method is called.
 *
 * Parameters: None.
 *
 * Returns: Nothing.
 */
void Drawable::show(void)
{
    m_visible = true;
}

/* isVisible()
 *
 * Predicate to determine if an object is visible.
 *
 * Parameters: None.
 *
 * Returns: A bool indicating whether the object is visible.
 */
bool Drawable::isVisible(void) const
{
    return m_visible;
}


/* hide()
 *
 * Causes sprite to not be drawn when the draw() method is called.
 *
 * Parameters: None.
 *
 * Returns: Nothing.
 */
void Drawable::hide(void)
{
    m_visible = false;
}

