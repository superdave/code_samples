/*
 *  PNGImage.h
 *  -BLAM-
 *
 *  Created by David Riley on 10/28/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#ifndef PNGIMAGE_H
#define PNGIMAGE_H

#include "Exception.h"
#include "Image.h"

DECLARE_EXCEPTION(PNGException)

class PNGImage : public Image
{
public:
    /* PNGImage(filename)
     *
     * Attempts to open a PNG file using LibPNG and create an image with it.
     *
     * Parameters:
     *    filename: The filename of the image to be opened.
     */
    PNGImage(const char *filename);
    
    /* ~PNGImage()
     *
     * Cleans up after the Image.
     */
    virtual ~PNGImage(void);
};


#endif // PNGIMAGE_H
