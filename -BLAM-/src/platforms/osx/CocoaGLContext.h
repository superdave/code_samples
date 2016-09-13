/*
 *  CocoaGLContext.h
 *  -BLAM-
 *
 *  Created by David Riley on 10/29/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#ifndef COCOAGLCONTEXT_H
#define COCOAGLCONTEXT_H

#include "GLContext.h"

#include <Cocoa/Cocoa.h>
#include <OpenGL/CGLTypes.h>

class CocoaGLContext : public GLContext
{
public:
    /* CocoaGLContext(ctx)
     *
     * Creates a C++ wrapper around a Cocoa OpenGL context.
     *
     * Parameters:
     *    ctx: The NSOpenGLContext to wrap around.
     */
    CocoaGLContext(NSOpenGLContext *ctx);
    
    /* ~CocoaGLContext()
     *
     * Cleans up after the context wrapper is done.
     */
    ~CocoaGLContext(void);

    /* swap(void)
     *
     * Performs the platform-specific buffer swap.
     *
     * Parameters: None.
     *
     * Returns: Nothing.
     */
    virtual void swap(void);
    
    /* getHeight()
     *
     * Retrieves the context's height in pixels.
     *
     * Parameters: None.
     *
     * Returns: An int representing the height in pixels.
     */
    virtual float getHeight(void) const;

    /* getWidth()
     *
     * Retrieves the context's width in pixels.
     *
     * Parameters: None.
     *
     * Returns: An int representing the width in pixels.
     */
    virtual float getWidth(void) const;
    
    /* getColorSize()
     *
     * Retrieves the total bits per pixel.
     *
     * Parameters: None.
     *
     * Returns: An int representing the total bits per pixel of the context.
     */
    virtual unsigned int getColorSize(void) const;
    
    /* getDepthSize()
     *
     * Retrieves the size of the depth buffer.
     *
     * Parameters: None.
     *
     * Returns: An int representing the total bits in the depth buffer.
     */
    virtual unsigned int getDepthSize(void) const;
    
    /* update()
     *
     * Performs an internal update of the OpenGL context.
     *
     * Parameters: None.
     *
     * Returns: Nothing.
     */
    virtual void update(void);

    /* lock()
     *
     * Locks the context for thread safety.
     *
     * Parameters: None.
     *
     * Returns: Nothing.
     */
    virtual void lock(void);
    
    /* unlock()
     *
     * Unlocks the context for thread safety.
     *
     * Parameters: None.
     *
     * Returns: Nothing.
     */
    virtual void unlock(void);

protected:
    
    // Our context (both Cocoa and Carbon).
    NSOpenGLContext *m_ctx;
    CGLContextObj    m_cgl_ctx;
};
    

#endif // COCOAGLCONTEXT_H
