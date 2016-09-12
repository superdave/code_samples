#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>

#include "ListCell.h"

template <class T>
class List
{
   // The count of items in the list.
   int m_size;

   // Our data set.
   ListCell<T> *m_head, *m_tail;

  public:

   // --- Constructors / Destructors
   
   // No arguments need to be supplied.  Isn't that nice?
   List(void);

   ~List(void);

   // --- Mutators
   
   // Removes the item from the list.  Technically, one could just call the
   //  method directly on the list cell object, which is what this does, but
   //  that wouldn't update the list count, which would cause problems.
   void removeFromList(ListCell<T> *obj);

   // Adds an item to the list and returns a pointer to the cell for use later.
   //  Stores on the front of the list.
   ListCell<T> * addToFrontOfList(const T &data);

   // Adds an item to the list and returns a pointer to the cell for use later.
   //  Stores on the back of the list.
   ListCell<T> * addToBackOfList(const T &data);

   // Basically just an alias for addToFrontOfList().
   ListCell<T> * push(const T &data);

   // Removes the head element and returns its data value.
   const T pop(void);

   // Adds the contents of the lists together.
   void splice(List<T> *rhs);

   // --- Accessors

   // Gets the head of the list.
   ListCell<T> * getHead(void) const;

   // Gets the tail of the list.
   ListCell<T> * getTail(void) const;

   // Gets the current size of the list.
   int getCount(void) const;
};

#include "List.cpp"

#endif // __ LIST_H__
