/*
 *  FIFO.cpp
 *  -BLAM-
 *
 *  Created by David Riley on 11/10/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#include <stdio.h>

#include "FIFO.h"

/* FIFO(size)
 *
 * Initializes a lockless, thread-safe FIFO of the size requested.
 *
 * Parameters:
 *    size:      The number of slots to allocate.  In reality, there is one
 *               less than this number available.
 */
FIFO::FIFO(unsigned long size)
: m_head(0), m_tail(0), m_capacity(size - 1)
{
    // Allocate the space.
    m_objects = new Object * [size];
}

/* ~FIFO()
 *
 * Frees up the space required by a FIFO, and releases all objects still
 * remaining inside.
 */
FIFO::~FIFO(void)
{
    // Free everything up.
    while(Object *obj = this->pop())
    {
        obj->release();
    }
    
    delete [] m_objects;
}

/* isFull()
 *
 * Returns true if the FIFO is full, false otherwise.
 *
 * Parameters: None.
 *
 * Returns: True if the FIFO is full, false otherwise.
 */
bool FIFO::isFull(void) const
{
    // Get the empty space.
    if(m_tail > m_head) return (m_head == (m_tail - 1));
    else                return (m_head == m_capacity && m_tail == 0);
}

/* isEmpty()
 *
 * Returns true if the FIFO is empty, false otherwise.
 *
 * Parameters: None.
 *
 * Returns: True if the FIFO is empty, false otherwise.
 */
bool FIFO::isEmpty(void) const
{
    return m_tail == m_head;
}

/* push(obj)
 *
 * Puts an object into the FIFO if there is space for it.  If there is no
 * space, the insertion is rejected.  Any object successfully inserted is
 * retained.
 *
 * Parameters:
 *    obj: The object to be inserted.
 *
 * Returns: True if the object is successfully inserted, false otherwise.
 */
bool FIFO::push(Object *obj)
{
    // If it's full, take action.
    if(this->isFull()) return false;

    // Retain the object, just to be on the safe side.
    obj->retain();
    
    // Calculate the new head.
    unsigned int new_head = m_head + 1;
    if(new_head >= m_capacity) new_head = 0;
    
    // Add the object first.
    m_objects[m_head] = obj;
    
    // Now adjust the head.
    m_head = new_head;
    
    return true;
}
    
/* pop(obj)
 *
 * Removes an object from the FIFO if one exists.  If there are no objects
 * in the FIFO, nothing occurs.  Any objects removed should be released by
 * the calling function (and should therefore not be retained).
 *
 * Parameters: None.
 *
 * Returns: A pointer to the object requested, or NULL if the FIFO is empty.
 */
Object * FIFO::pop(void)
{
    // Is it empty?
    if(this->isEmpty()) return NULL;
    
    // Calculate the new tail.
    unsigned int new_tail = m_tail + 1;
    if(new_tail >= m_capacity) new_tail = 0;
    
    // Copy the object first.
    Object *obj = m_objects[m_tail];
    
    // Now adjust the head.
    m_tail = new_tail;
    
    // Return the object.
    return obj;
}

