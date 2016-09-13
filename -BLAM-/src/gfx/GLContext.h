/*
 *  GLContext.h
 *  -BLAM-
 *
 *  Created by David Riley on 10/29/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#ifndef GLCONTEXT_H
#define GLCONTEXT_H


class GLContext
{
public:
    /* ~GLContext()
     *
     * Cleans up after a context is done.
     */
    virtual ~GLContext(void);
    
    /* swap(void)
     *
     * Performs the platform-specific buffer swap.
     *
     * Parameters: None.
     *
     * Returns: Nothing.
     */
    virtual void swap(void) = 0;

    /* getHeight()
     *
     * Retrieves the context's height in pixels.
     *
     * Parameters: None.
     *
     * Returns: An int representing the height in pixels.
     */
    virtual float getHeight(void) const = 0;
    
    /* getWidth()
     *
     * Retrieves the context's width in pixels.
     *
     * Parameters: None.
     *
     * Returns: An int representing the width in pixels.
     */
    virtual float getWidth(void) const = 0;
    
    /* getColorSize()
     *
     * Retrieves the total bits per pixel.
     *
     * Parameters: None.
     *
     * Returns: An int representing the total bits per pixel of the context.
     */
    virtual unsigned int getColorSize(void) const = 0;
    
    /* getDepthSize()
     *
     * Retrieves the size of the depth buffer.
     *
     * Parameters: None.
     *
     * Returns: An int representing the total bits in the depth buffer.
     */
    virtual unsigned int getDepthSize(void) const = 0;
    
    /* update()
     *
     * Performs an internal update of the OpenGL context.
     *
     * Parameters: None.
     *
     * Returns: Nothing.
     */
    virtual void update(void) = 0;
    
    /* lock()
     *
     * Locks the context for thread safety.
     *
     * Parameters: None.
     *
     * Returns: Nothing.
     */
    virtual void lock(void) = 0;
    
    /* unlock()
     *
     * Unlocks the context for thread safety.
     *
     * Parameters: None.
     *
     * Returns: Nothing.
     */
    virtual void unlock(void) = 0;
    
protected:
    /* GLContext()
     *
     * Creates a GLContext.  We make this protected so that bare GLContext
     * objects can't be instantiated.
     *
     * Parameters: None.
     */
    GLContext(void);
};
    

#endif // GLCONTEXT_H
