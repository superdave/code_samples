/*
 *  DataObject.cpp
 *  -BLAM-
 *
 *  Created by David Riley on 11/7/09.
 *  Copyright 2009 Insanely Great Software. All rights reserved.
 *
 */

#include "DataObject.h"

#ifndef DATAOBJECT_CPP
#define DATAOBJECT_CPP

#include <stdint.h>

/* DataObject(size)
 *
 * Creates a new DataObject, allocating space for the requested amount.
 *
 * Parameters:
 *    size: The size of data requested.
 */
template <class T>
DataObject<T>::DataObject(unsigned long count)
{
    // Allocate the new object.
    data = new T [count];
}

/* ~DataObject()
 *
 * Cleans up after a DataObject, mostly just releasing the memory held.
 */
template <class T>
DataObject<T>::~DataObject(void)
{
    delete [] data;
}

template <class T>
DataObject<T>::operator T * (void)
{
    return data;
}

template <class T>
DataObject<T>::operator const T * (void) const
{
    return data;
}


#endif // DATAOBJECT_CPP

