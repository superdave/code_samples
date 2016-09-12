#ifndef __LISTPAIRCELL_H__
#define __LISTPAIRCELL_H__

// Ew, templates.  Why didn't I use Java?
template <class T>
class ListPairCell
{
   // The linked list elements.
   ListPairCell<T> *m_next, *m_prev;

   // The "index" pointer: a pointer to the pointer in the main list which
   //  points to this cell.
   ListPairCell<T> **m_index;

   // The data.  This is a pointer to make memory management a bit easier.
   T *m_data;

  public:
   

   // --- Constructors

   // The constructor takes a link to both sides of it and a pointer to its
   //  data area.
   ListPairCell(ListPairCell<T> *next,
		ListPairCell<T> *prev,
		ListPairCell<T> **index,
		T *data);

   // --- Mutators

   // setData(): Sets the internal data of the cell (and its sibling) to the
   //  supplied data.
   void setData(T data);
   
   // setNext(): Sets the next element of the cell to be the supplied element,
   //  and sets that element's previous to this one (if it's not set already).
   void setNext(ListPairCell<T> *next);

   // setPrev(): Similar to setNext(), but backwards.
   void setPrev(ListPairCell<T> *prev);

   // SetIndex(): Sets the index of this cell, and sets this as the destination
   //  of that pointer.
   void setIndex(ListPairCell<T> **index);

   // Removes this cell from the current list, and marks its index pointer
   //  as NULL.  Returns a boolean indicating whether the removal was
   //  successful (i.e. it is a failure if the item has already been removed).
   bool removeFromList(void);
   

   // --- Accessors
   
   // getData(): This function is a mystery.
   const T & getData(void) const;

   // getNext(): Gets the next element of the list.
   ListPairCell<T> * getNext(void) const;

   // getPrev(): Similar to getNext(), but backwards.
   ListPairCell<T> * getPrev(void) const;

   // getIndex: Gets the the index pointer of the cell.  Could be NULL if the
   //  cell has already been removed.
   ListPairCell<T> ** getIndex(void) const;
};

#include "ListPairCell.cpp"

#endif // __LISTPAIRCELL_H__
