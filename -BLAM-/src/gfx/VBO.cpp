/*
 *  VBO.cpp
 *  -BLAM-
 *
 *  Created by David Riley on 11/9/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#include "VBO.h"

/* VBO(vertices, indices, count)
 *
 * Allocates and creates a Vertex Buffer Object pair for both vertices and
 * indices.
 */
VBO::VBO(const Graphics_Point *vertices,
         const unsigned int   *indices,
         unsigned int          vertCount,
         unsigned int          indexCount,
         GLenum                mode)
: m_vertices(0),
  m_indices(0),
  m_count(indices ? indexCount : vertCount),
  m_mode(mode)
{
    if(vertices)
    {
        // Allocate a vertex buffer.
        glGenBuffersARB(1, &m_vertices);
    
        // Bind the buffer.
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_vertices);
        
        // Set the data.
        glBufferDataARB(GL_ARRAY_BUFFER_ARB,
                        vertCount * sizeof(*vertices), 
                        vertices,
                        GL_STATIC_DRAW_ARB);
    }
    
    // Same with the index buffer.
    if(indices)
    {
        glGenBuffersARB(1, &m_indices);

        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_indices);
    
        glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB,
                    indexCount * sizeof(*indices), 
                    indices,
                    GL_STATIC_DRAW_ARB);
    }
}

/* ~VBO()
 *
 * Deletes the contents of a VBO pair.
 */
VBO::~VBO(void)
{
    // Clean up.
    if(m_vertices) glDeleteBuffersARB(1, &m_vertices);
    if(m_indices)  glDeleteBuffersARB(1, &m_indices);
}

/* bind()
 *
 * Binds the VBO pair.
 */
void VBO::bind(void)
{
    if(m_vertices)
    {
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_vertices);
        // Set the drawing arrays.
        glInterleavedArrays(GL_T2F_C4F_N3F_V3F,
                            sizeof(Graphics_Point),
                            0);
    }
    
    if(m_indices)  glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_indices);
}
    
    
/* draw()
 *
 * Draws the VBO pair.
 */
void VBO::draw(void)
{
    // Bind them properly.
    this->bind();

    // If we have an index buffer, draw the elements.
    if(m_indices)
    {
        glDrawElements(m_mode, m_count, GL_UNSIGNED_INT, 0);
    } else {
        // Otherwise, just blast out the vertices.
        glDrawArrays(m_mode, 0, m_count);
    }
    
}

