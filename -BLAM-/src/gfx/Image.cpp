/*
 *  Image.cpp
 *  -BLAM-
 *
 *  Created by David Riley on 10/28/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#include <stdio.h>
#include <string.h>

#include "Exception.h"
#include "Image.h"

#include "PNGImage.h"

/* Image(name)
 *
 * Creates a NULL image.
 *
 * Parameters:
 *    name: The name to give the image.
 */
Image::Image(const char *name)
: m_data(NULL),
m_width(0),
m_height(0),
m_bitsPerChannel(0),
m_numChannels(0),
m_hasAlpha(false),
m_hasFloatData(false)
{
    // If our name is NULL, just go with that.
    if(name == NULL)
    {
        m_name = NULL;
    } else {
        // Otherwise...
        m_name = new char[strlen(name) + 1];
        
        strcpy((char *)m_name, name);
    }
}

/* ~Image()
 *
 * Cleans up an Image (mostly just the name).
 */
Image::~Image(void)
{
    if(m_name != NULL)
        delete[] m_name;
}

/* getName()
 *
 * Retrieves the name used by an image.
 *
 * Parameters: None.
 *
 * Returns: A string representing the name of the image.
 */
const char * Image::getName(void) const
{
    return m_name;
}

/* getData()
 *
 * Retrieves the data representing the image.
 *
 * Parameters: None.
 *
 * Returns: A pointer to the data represented by the image, or NULL if no
 *          valid image data is present.
 */
const void * Image::getData(void) const
{
    return m_data;
}

/* getWidth()
 *
 * Retrieves the width of the image.
 *
 * Parameters: None.
 *
 * Returns: An int representing the width (in pixels) of the image.
 */
unsigned int Image::getWidth(void) const
{
    return m_width;
}

/* getHeight()
 *
 * Retrieves the height of the image.
 *
 * Parameters: None.
 *
 * Returns: An int representing the height (in pixels) of the image.
 */
unsigned int Image::getHeight(void) const
{
    return m_height;
}

/* getBitsPerChannel()
 *
 * Retrieves the number of bits per channel of an image.
 *
 * Parameters: None.
 *
 * Returns: An int representing the number of bits per channel.
 */
unsigned int Image::getBitsPerChannel(void) const
{
    return m_bitsPerChannel;
}

/* getNumChannels()
 *
 * Retrieves the number of channels in an image.
 *
 * Parameters: None.
 *
 * Returns: An int representing the number of channels in an image.
 */
unsigned int Image::getNumChannels(void) const
{
    return m_numChannels;
}

/* hasAlpha()
 *
 * Predicate to determine if an image has an alpha channel.
 *
 * Parameters: None.
 *
 * Returns: A boolean indicating whether there is an alpha channel.
 */
bool Image::hasAlpha(void) const
{
    return m_hasAlpha;
}

/* hasFloatData()
 *
 * Predicate to determine if the image data is a floating-point format.
 *
 * Parameters: None.
 *
 * Returns: A boolean indicating whether the data is floating-point.
 */
bool Image::hasFloatData() const
{
    return m_hasFloatData;
}

/* getImageType()
 *
 * Returns a constant representing the image type.
 *
 * Parameters: None.
 *
 * Returns: A constant indicating the data format of the image.
 */
ImageType Image::getImageType(void) const
{
    return m_imageType;
}

/* static load(filename)
 *
 * Attempts to load a graphics file by using its extension to determine the
 * type and creating the appropriate Image class.
 *
 * Parameters:
 *    filename: The pathname of the file to try to open.
 *
 * Returns: A pointer to an Image subclass for the appropriate filetype.
 *
 * Throws:
 *    FileException:        If there is an error opening or reading the
 *                          file.
 *    UnknownTypeException: If the type of the file is not one we handle.
 */
Image * Image::load(const char *filename)
{
    // Sanity check.
    ASSERT_EXCEPTION(filename != NULL,
                     FileException,
                     "NULL filename");
    
    // Try to get the extension of the filename.
    const char *extension = NULL;
    for(const char *cur = filename; *cur != '\0'; cur++)
    {
        if(*cur == '.') extension = cur;
    }
    
    // Did we find an extension?
    ASSERT_EXCEPTION(extension != NULL,
                     UnknownTypeException,
                     "No extension on filename.");
    
    // Check to see if it's a file type we know.
    if(!strcmp(extension, ".png"))
    {
        // Get a PNG image.
        return new PNGImage(filename);
    }
    
    // If we got here, we don't know the type of the file.
    RAISE_EXCEPTION(UnknownTypeException,
                    "Unknown graphics filetype: %s", extension);
    
    return NULL;
}
    
    
    
