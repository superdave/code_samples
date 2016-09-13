/*
 *  CocoaGLContext.mm
 *  -BLAM-
 *
 *  Created by David Riley on 10/29/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#include "gl_config.h"

#include "CocoaGLContext.h"




/* CocoaGLContext(ctx)
 *
 * Creates a C++ wrapper around a Cocoa OpenGL context.
 *
 * Parameters:
 *    ctx: The NSOpenGLContext to wrap around.
 */
CocoaGLContext::CocoaGLContext(NSOpenGLContext *ctx)
: m_ctx(ctx)
{
    // Make sure we keep that context.
    [m_ctx retain];
    
    // Get the CGL context as well.
    m_cgl_ctx = (CGLContextObj)[m_ctx CGLContextObj];
}

/* ~CocoaGLContext()
 *
 * Cleans up after the context wrapper is done.
 */
CocoaGLContext::~CocoaGLContext(void)
{
    // Release the context.
    [m_ctx release];
}

/* swap(void)
 *
 * Performs the platform-specific buffer swap.
 *
 * Parameters: None.
 *
 * Returns: Nothing.
 */
void CocoaGLContext::swap(void)
{
    // Just do the swap.
    [m_ctx flushBuffer];
}

/* getHeight()
 *
 * Retrieves the context's height in pixels.
 *
 * Parameters: None.
 *
 * Returns: An int representing the height in pixels.
 */
float CocoaGLContext::getHeight(void) const
{
    NSRect frame = [[m_ctx view] frame];
    
    float width = frame.size.height;
    
    return width;
}

/* getWidth()
 *
 * Retrieves the context's width in pixels.
 *
 * Parameters: None.
 *
 * Returns: An int representing the width in pixels.
 */
float CocoaGLContext::getWidth(void) const
{
    NSRect frame = [[m_ctx view] frame];
    
    float width = frame.size.width;
    
    return width;
}

/* getColorSize()
 *
 * Retrieves the total bits per pixel.
 *
 * Parameters: None.
 *
 * Returns: An int representing the total bits per pixel of the context.
 */
unsigned int CocoaGLContext::getColorSize(void) const
{
    // Get the pixel format.
    CGLPixelFormatObj pf = CGLGetPixelFormat(m_cgl_ctx);
    
    // Get the virtual screen.
    GLint screen;
    CGLGetVirtualScreen(m_cgl_ctx, &screen);
    
    // Get the depth.
    GLint depth;
    CGLDescribePixelFormat(pf,
                           screen,
                           kCGLPFAColorSize,
                           &depth);
    
    return depth;
}
    

/* getDepthSize()
 *
 * Retrieves the size of the depth buffer.
 *
 * Parameters: None.
 *
 * Returns: An int representing the total bits in the depth buffer.
 */
unsigned int CocoaGLContext::getDepthSize(void) const
{
    // Get the pixel format.
    CGLPixelFormatObj pf = CGLGetPixelFormat(m_cgl_ctx);
    
    // Get the virtual screen.
    GLint screen;
    CGLGetVirtualScreen(m_cgl_ctx, &screen);
    
    // Get the depth.
    GLint depth;
    CGLDescribePixelFormat(pf,
                           screen,
                           kCGLPFADepthSize,
                           &depth);
    
    return depth;
}

/* update()
 *
 * Performs an internal update of the OpenGL context.
 *
 * Parameters: None.
 *
 * Returns: Nothing.
 */
void CocoaGLContext::update(void)
{
    [m_ctx update];
}

/* lock()
 *
 * Locks the context for thread safety.
 *
 * Parameters: None.
 *
 * Returns: Nothing.
 */
void CocoaGLContext::lock(void)
{
    CGLLockContext(m_cgl_ctx);
}

/* unlock()
 *
 * Unlocks the context for thread safety.
 *
 * Parameters: None.
 *
 * Returns: Nothing.
 */
void CocoaGLContext::unlock(void)
{
    CGLUnlockContext(m_cgl_ctx);
}


