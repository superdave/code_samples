/*
 *  DataObject.h
 *  -BLAM-
 *
 *  Created by David Riley on 11/7/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include "Object.h"

template<class T>

class DataObject : public Object
{
public:
    /* DataObject(size)
     *
     * Creates a new DataObject, allocating space for the requested amount.
     *
     * Parameters:
     *    size: The number of objects requested.
     */
    DataObject(unsigned long count);
    
    /* ~DataObject()
     *
     * Cleans up after a DataObject, mostly just releasing the memory held.
     */
    virtual ~DataObject(void);
    
    operator T * (void);
    
    operator const T * (void) const;
    
    // The data we're watching.
    T *data;
};

#include "DataObject.cpp"

#endif // DATAOBJECT_H
