/*
 *  Texture.h
 *  -BLAM-
 *
 *  Created by David Riley on 10/24/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#ifndef BLAM_TEXTURE_H
#define BLAM_TEXTURE_H

#include "gl_config.h"

#include "Object.h"

#include "Image.h"

class Texture : public Object
{
public:
    /* Texture(filename, type)
     *
     * Creates a new texture loaded from a file.  The graphics library will
     * attempt to autodetect the filetype and, optionally, the texture type.
     *
     * Parameters:
     *    filename: The pathname to the file to load.
     *    type:     The internal GL representation of the texture type.  If this
     *              is -1, the type is determined from the graphic file type.
     */
    Texture(const char *filename, GLenum type = -1);
    
    /* Texture(data, width, height, type, fmt)
     *
     * Creates a new texture from raw data.  The caller must specify the texture
     * format.
     *
     * Parameters:
     *    data:   The raw data from which the texture is to be created.
     *    width:  The width of the image.
     *    height: The height of the image.
     *    type:   The GL representation format of the data.
     *    fmt:    The GL format of the image channels (GL_BYTE, GL_FLOAT, etc).
     */
    Texture(const void *data,
            unsigned int width,
            unsigned int height,
            GLenum type,
            GLenum fmt);
    
    /* ~Texture()
     *
     * Cleans up after the texture, deallocating any buffers that may be in
     * use and freeing up the textures.
     */
    virtual ~Texture(void);
    
    /* bind(unit)
     *
     * Binds the texture to the indicated texture unit.
     *
     * Parameters:
     *    unit: The texture unit to bind to.  Defaults to zero.
     *
     * Returns: Nothing.
     */
    virtual void bind(unsigned int unit = 0);
    
    /* isValid()
     *
     * Tests whether the texture is valid (generally using glIsTexture()).
     *
     * Parameters: None.
     *
     * Returns: Nothing.
     */
    virtual bool isTexture(void);
    
    /* getWidth()
     *
     * Gets the width of the texture image.
     *
     * Parameters: None.
     *
     * Returns: An int representing the width, in pixels, of the texture.
     */
    unsigned int getWidth(void) const;
    
    /* getHeight()
     *
     * Gets the height of the texture image.
     *
     * Parameters: None.
     *
     * Returns: An int representing the height, in pixels, of the texture.
     */
    unsigned int getHeight(void) const;
    
private:
    
    // The texture ID.
    unsigned int  m_id;
    
    // The underlying width and height.
    unsigned int  m_width;
    unsigned int  m_height;
};


#endif // BLAM_TEXTURE_H
