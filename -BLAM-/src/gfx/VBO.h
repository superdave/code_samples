/*
 *  VBO.h
 *  -BLAM-
 *
 *  Created by David Riley on 11/9/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#ifndef VBO_CPP
#define VBO_CPP

#include "Object.h"

#include "gl_config.h"
#include "geometry.h"

class VBO : public Object
{
public:
    /* VBO(vertices, indices, count)
     *
     * Allocates and creates a Vertex Buffer Object pair for both vertices and
     * indices.
     */
    VBO(const Graphics_Point *vertices,
        const unsigned int   *indices,
        unsigned int          vertCount,
        unsigned int          indexCount,
        GLenum                mode);
    
    /* ~VBO()
     *
     * Deletes the contents of a VBO pair.
     */
    virtual ~VBO(void);
    
    /* bind()
     *
     * Binds the VBO pair.
     */
    void bind(void);
    
    /* draw()
     *
     * Draws the VBO pair.
     */
    void draw(void);
    
protected:
    
    // The VBO handles for the vertices and indices.
    unsigned int m_vertices, m_indices;
    
    // The count of vertices and indices.
    unsigned int m_count;
    
    // The mode to draw in.
    GLenum       m_mode;
};





#endif // VBO_CPP
