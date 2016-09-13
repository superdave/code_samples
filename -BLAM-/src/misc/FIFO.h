/*
 *  FIFO.h
 *  -BLAM-
 *
 *  Created by David Riley on 11/10/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#ifndef FIFO_H
#define FIFO_H

#include "Object.h"

class FIFO
{
public:
    /* FIFO(size)
     *
     * Initializes a lockless, thread-safe FIFO of the size requested.
     *
     * Parameters:
     *    size:      The number of slots to allocate.  In reality, there is one
     *               less than this number available.
     */
    FIFO(unsigned long size);
    
    /* ~FIFO()
     *
     * Frees up the space required by a FIFO, and releases all objects still
     * remaining inside.
     */
    ~FIFO(void);
    
    /* isFull()
     *
     * Returns true if the FIFO is full, false otherwise.
     *
     * Parameters: None.
     *
     * Returns: True if the FIFO is full, false otherwise.
     */
    bool isFull(void) const;
    
    /* isEmpty()
     *
     * Returns true if the FIFO is empty, false otherwise.
     *
     * Parameters: None.
     *
     * Returns: True if the FIFO is empty, false otherwise.
     */
    bool isEmpty(void) const;
    
    /* push(obj)
     *
     * Puts an object into the FIFO if there is space for it.  If there is no
     * space, the oldest object is overwritten (and released) if the overwrite
     * parameter is set, otherwise the insertion is rejected.  Any object
     * successfully inserted is retained.
     *
     * Parameters:
     *    obj: The object to be inserted.
     *
     * Returns: True if the object is successfully inserted, false otherwise.
     */
    bool push(Object *obj);
    
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
    Object * pop(void);
    
protected:
    
    // The objects.
    Object **m_objects;
    
    // The head and tail counters for the object.
    unsigned long m_head, m_tail;
    
    // The capacity of the object.
    unsigned long m_capacity;
};


#endif // FIFO_H
