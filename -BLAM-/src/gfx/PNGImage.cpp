/*
 *  PNGImage.cpp
 *  -BLAM-
 *
 *  Created by David Riley on 10/28/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#include <stdio.h>
#include <stdint.h>

#include "util.h"

#include "PNGImage.h"

#include "Exception.h"

#include "png.h"

/* PNGImage(filename)
 *
 * Attempts to open a PNG file using LibPNG and create an image with it.
 *
 * Parameters:
 *    filename: The filename of the image to be opened.
 */
PNGImage::PNGImage(const char *filename)
: Image(filename)
{
    // Start by trying to open the file.
    FILE *fp = fopen(filename, "rb");
    
    // Did it open?
    ASSERT_EXCEPTION(fp != NULL,
                     FileException,
                     "Failed to open file \"%s\"", filename);
    
    // Read 8 bytes for the signature.
	uint8_t sig[8];
	size_t count = fread(sig, 1, 8, fp);
	
	// Check the size we read.
	ASSERT_EXCEPTION(count == 8,
                     FileException,
                     "Unexpected EOF reading PNG signature in \"%s\"",
                     filename);
    
    // Check the header against the PNG library.
	ASSERT_EXCEPTION(!png_sig_cmp(sig, 0, count),
                     PNGException,
                     "Not a PNG file: \"%s\"", filename);
	
	// Make our read struct.
	png_struct *read_struct = png_create_read_struct(PNG_LIBPNG_VER_STRING,
													 NULL,
													 NULL,
													 NULL);
	
	// Check the data.
	ASSERT_EXCEPTION(read_struct != NULL,
                     PNGException,
                     "Failed to create read struct while reading \"%s\"",
                     filename);
	
	// Make the info struct.
	png_info *info_struct = png_create_info_struct(read_struct);
	
	// Check this one, too.
	ASSERT_EXCEPTION(info_struct != NULL,
                     PNGException,
                     "Failed to create info struct while reading \"%s\"",
                     filename);
	
	// And make the end info struct.
	png_info *end_struct = png_create_info_struct(read_struct);
    
	// And check it.
	ASSERT_EXCEPTION(end_struct != NULL,
                     PNGException,
                     "Failed to create end info struct while reading\"%s\"",
                     filename);
	
	// Do our setjmp thang.  I'm pretty sure this isn't thread-safe.
	if(setjmp(png_jmpbuf(read_struct)))
	{
		// If we failed, clean up and throw the exception.
		png_destroy_read_struct(&read_struct,
								&info_struct,
								&end_struct);
		
		// Close the file, too.
		fclose(fp);
		
		RAISE_EXCEPTION(PNGException,
                        "Error reading PNG file: \"%s\"",
                        filename);
	}
	
    // Initialize the IO for stdio.
	png_init_io(read_struct, fp);
	
	// We read a few bytes at the beginning.
	png_set_sig_bytes(read_struct, (int)count);
	
	// At the moment, we're not dealing with unknown chunks.
	
	// Read in the PNG.  Our options:
	//
	// - Expand 1, 2 and 4 bit samples to bytes.
	png_read_png(read_struct,
				 info_struct, 
				 PNG_TRANSFORM_PACKING,
				 NULL);
	
	// Find out our image sizes and attributes.
	m_width = png_get_image_width(read_struct, info_struct);
	m_height = png_get_image_height(read_struct, info_struct);
	m_numChannels = png_get_channels(read_struct, info_struct);
    m_bitsPerChannel = png_get_bit_depth(read_struct, info_struct);
    
    // Figure out the color type, mostly for hasAlpha().
    int colorType = png_get_color_type(read_struct, info_struct);
    m_hasAlpha = (colorType & PNG_COLOR_MASK_ALPHA) != 0;
    m_hasFloatData = false;
    
    // Compose everything into an image type.
    if(m_bitsPerChannel == 8) m_imageType = IMAGE_TYPE_UINT8;
    else                      m_imageType = IMAGE_TYPE_UINT16;
    
    // Get our rowbytes, which we'll need for allocating the memory.
    unsigned int rowBytes = png_get_rowbytes(read_struct, info_struct);
    unsigned int memSize = rowBytes * m_height;
    
    // Allocate our data.
    m_data = malloc(memSize);
		
	dprintf("Reading PNG image \"%s\" (%dx%dx%d)\n",
			filename,
			m_width,
			m_height,
			m_numChannels * m_bitsPerChannel / 8);
	
    // Get the PNG rows.
	uint8_t **rows = (uint8_t **)png_get_rows(read_struct, info_struct);

    // Go through them and copy into the upper-left corner of the picture.
	for(unsigned int i = 0; i < m_height; i++)
	{
		memcpy((uint8_t *)m_data + ((m_height - i - 1) * rowBytes),
               rows[i],
               rowBytes);
	}
	
    // We're pretty much done here.
	png_destroy_read_struct(&read_struct,
							&info_struct,
							&end_struct);
}    
    
    
/* ~PNGImage()
 *
 * Cleans up after the Image.
 */
PNGImage::~PNGImage(void)
{
    // Just erase the image.
    if(m_data != NULL) free(m_data);
}
