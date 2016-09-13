/*
 *  Image.h
 *  -BLAM-
 *
 *  Created by David Riley on 10/28/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#ifndef IMAGE_H
#define IMAGE_H

#include "Object.h"

typedef enum
{
    IMAGE_TYPE_UINT8,
    IMAGE_TYPE_INT8,
    IMAGE_TYPE_UINT16,
    IMAGE_TYPE_INT16,
    IMAGE_TYPE_UINT32,
    IMAGE_TYPE_INT32,
    IMAGE_TYPE_FLOAT,
    IMAGE_TYPE_DOUBLE
} ImageType;

class Image : public Object
{
public:
    /* Image(name)
     *
     * Creates a NULL image.
     *
     * Parameters:
     *    name: The name to give the image.
     */
    Image(const char *name);
    
    /* ~Image()
     *
     * Cleans up an Image (mostly just the name).
     */
    virtual ~Image(void);
    
    /* getName()
     *
     * Retrieves the name used by an image.
     *
     * Parameters: None.
     *
     * Returns: A string representing the name of the image.
     */
    virtual const char * getName(void) const;
    
    /* getData()
     *
     * Retrieves the data representing the image.
     *
     * Parameters: None.
     *
     * Returns: A pointer to the data represented by the image, or NULL if no
     *          valid image data is present.
     */
    virtual const void * getData(void) const;
    
    /* getWidth()
     *
     * Retrieves the width of the image.
     *
     * Parameters: None.
     *
     * Returns: An int representing the width (in pixels) of the image.
     */
    virtual unsigned int getWidth(void) const;
    
    /* getHeight()
     *
     * Retrieves the height of the image.
     *
     * Parameters: None.
     *
     * Returns: An int representing the height (in pixels) of the image.
     */
    virtual unsigned int getHeight(void) const;
    
    /* getBitsPerChannel()
     *
     * Retrieves the number of bits per channel of an image.
     *
     * Parameters: None.
     *
     * Returns: An int representing the number of bits per channel.
     */
    virtual unsigned int getBitsPerChannel(void) const;
    
    /* getNumChannels()
     *
     * Retrieves the number of channels in an image.
     *
     * Parameters: None.
     *
     * Returns: An int representing the number of channels in an image.
     */
    virtual unsigned int getNumChannels(void) const;
    
    /* hasFloatData()
     *
     * Predicate to determine if the image data is a floating-point format.
     *
     * Parameters: None.
     *
     * Returns: A boolean indicating whether the data is floating-point.
     */
    virtual bool hasFloatData() const;
    
    /* hasAlpha()
     *
     * Predicate to determine if an image has an alpha channel.
     *
     * Parameters: None.
     *
     * Returns: A boolean indicating whether there is an alpha channel.
     */
    virtual bool hasAlpha(void) const;
    
    /* getImageType()
     *
     * Returns a constant representing the image type.
     *
     * Parameters: None.
     *
     * Returns: A constant indicating the data format of the image.
     */
    virtual ImageType getImageType(void) const;
    
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
    static Image * load(const char *filename);
    
protected:
    
    // Our image name.
    const char *m_name;
    
    // Our image data.
    void *m_data;
    
    // General properties of the image (these can be overridden by subclasses
    // by overriding the virtual accessor methods).
    unsigned int m_width;
    unsigned int m_height;
    unsigned int m_bitsPerChannel;
    unsigned int m_numChannels;
    bool         m_hasAlpha;
    bool         m_hasFloatData;
    ImageType    m_imageType;
};


#endif // IMAGE_H

