/*
 *  Texture.cpp
 *  -BLAM-
 *
 *  Created by David Riley on 10/24/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#include "Texture.h"
#include "Exception.h"
#include "Image.h"

GLenum g_types[] =
{
GL_UNSIGNED_BYTE,
GL_BYTE,
GL_UNSIGNED_SHORT,
GL_SHORT,
GL_UNSIGNED_INT,
GL_INT,
GL_FLOAT
};

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
Texture::Texture(const char *filename, GLenum type)
: m_id(0)
{
    // First, generate the texture ID.
    glGenTextures(1, &m_id);
    
    // Read in the texture.
    Image *tex = Image::load(filename);
    
    GLenum fmt = g_types[tex->getImageType()];
    
    // Check the texture type.  Do we have to determine it?
    if(type == -1)
    {
        switch(tex->getNumChannels())
        {
            case 1:
                if(tex->hasAlpha()) type = GL_ALPHA;
                else         type = GL_LUMINANCE;
                break;
                
            case 2:
                type = GL_LUMINANCE_ALPHA;
                break;
                
            case 3:
                type = GL_RGB;
                break;
                
            case 4:
                type = GL_RGBA;
                break;
                
            default:
                type = GL_RGB;
        }
    }
    
    // Bind to the texture before creating it.
    this->bind();
    
    // Get the width and height.
    m_width = tex->getWidth();
    m_height = tex->getHeight();
        
    // Create the texture.
    glTexImage2D(GL_TEXTURE_RECTANGLE_ARB,
                 0,
                 type,
                 m_width,
                 m_height,
                 0,
                 type,
                 fmt,
                 tex->getData());
    
    // We're done with the image.  Keep it around for later.
    tex->release();

    // Check for errors.
    GLenum err = glGetError();
    if(err)
        printf("GL Error: %s\n", gluErrorString(err));
}

/* Texture(data, type)
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
Texture::Texture(const void *data,
                 unsigned int width,
                 unsigned int height,
                 GLenum type,
                 GLenum fmt)
: m_id(0)
{
    // Generate the texture ID.
    glGenTextures(1, &m_id);
    
    // Bind to it.
    this->bind();
    
    // Create the texture.
    glTexImage2D(GL_TEXTURE_RECTANGLE_ARB,
                 0,
                 type,
                 width,
                 height,
                 0,
                 type,
                 fmt,
                 data);
    
}

/* ~Texture()
 *
 * Cleans up after the texture, deallocating any buffers that may be in
 * use and freeing up the textures.
 */
Texture::~Texture(void)
{
    // Delete the underlying texture.
    glDeleteTextures(1, &m_id);
}

/* bind(unit)
 *
 * Binds the texture to the indicated texture unit.
 *
 * Parameters:
 *    unit: The texture unit to bind to.  Defaults to zero.
 *
 * Returns: Nothing.
 */
void Texture::bind(unsigned int unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);
    
    glBindTexture(GL_TEXTURE_RECTANGLE_ARB, m_id);
}
    
/* isValid()
 *
 * Tests whether the texture is valid (generally using glIsTexture()).
 *
 * Parameters: None.
 *
 * Returns: Nothing.
 */
bool Texture::isTexture(void)
{
    return (GL_FALSE != glIsTexture(m_id));
}

/* getWidth()
 *
 * Gets the width of the texture image.
 *
 * Parameters: None.
 *
 * Returns: An int representing the width, in pixels, of the texture.
 */
unsigned int Texture::getWidth(void) const
{
    return m_width;
}

/* getHeight()
 *
 * Gets the height of the texture image.
 *
 * Parameters: None.
 *
 * Returns: An int representing the height, in pixels, of the texture.
 */
unsigned int Texture::getHeight(void) const
{
    return m_height;
}


