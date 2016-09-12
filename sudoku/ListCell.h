#ifndef __LISTCELL_H__
#define __LISTCELL_H__

#include <iostream>

// Ew, templates.  Why didn't I use Java?
template <class T>
class ListCell
{
   // The linked list elements.
   ListCell<T> *m_next, *m_prev;

   // The data.
   T m_data;

  public:
   
   // --- Constructors

   // The constructor takes a link to both sides of it and a pointer to its
   //  data area.
   ListCell(ListCell<T> *next = NULL, ListCell<T> *prev = NULL, T data = T());

   // --- Mutators

   // setData(): Sets the internal data of the cell (and its sibling) to the
   //  supplied data.
   void setData(T data);
   
   // setNext(): Sets the next element of the cell to be the supplied element,
   //  and sets that element's previous to this one (if it's not set already).
   void setNext(ListCell<T> *next);

   // setPrev(): Similar to setNext(), but backwards.
   void setPrev(ListCell<T> *prev);

   // Removes this cell from the current list
   void removeFromList(void);
   

   // --- Accessors
   
   // getData(): This function is a mystery.
   const T & getData(void) const;

   // getNext(): Gets the next element of the list.
   ListCell<T> * getNext(void) const;

   // getPrev(): Similar to getNext(), but backwards.
   ListCell<T> * getPrev(void) const;
};

#include "ListCell.cpp"

#endif // __LISTCELL_H__
