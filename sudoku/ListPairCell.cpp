#ifndef __LISTPAIRCELL_CPP__
#define __LISTPAIRCELL_CPP__

#include <stdio.h>

#include "ListPairCell.h"

// --- Constructors

// The constructor takes a link to both sides of it and a pointer to its
//  data area.
template<class T>
ListPairCell<T>::ListPairCell(ListPairCell<T> *next,
			      ListPairCell<T> *prev,
			      ListPairCell<T> **index,
			      T *data)
   : m_next(NULL), m_prev(NULL)
{
   setNext(next);
   setPrev(prev);

   m_index = index;

   *index = this;

   m_data = data;
}

// --- Mutators

// setData(): Sets the internal data of the cell (and its sibling) to the
//  supplied data.
template<class T>
void ListPairCell<T>::setData(T data)
{
   *m_data = data;
}
   
// setNext(): Sets the next element of the cell to be the supplied element,
//  and sets that element's previous to this one (if it's not set already).
template<class T>
void ListPairCell<T>::setNext(ListPairCell<T> *next)
{
   m_next = next;
   if(next != NULL && next->getPrev() != this) next->setPrev(this);
}

// setPrev(): Similar to setNext(), but backwards.
template<class T>
void ListPairCell<T>::setPrev(ListPairCell<T> *prev)
{
   m_prev = prev;
   if(prev != NULL && prev->getNext() != this) prev->setNext(this);
}

// SetIndex(): Sets the index of this cell, and sets this as the destination
//  of that pointer.
template<class T>
void ListPairCell<T>::setIndex(ListPairCell<T> **index)
{
   m_index = index;

   *index = this;
}

// Removes this cell from the current list, and marks its index pointer
//  as NULL.  Returns a boolean indicating whether the removal was
//  successful (i.e. it is a failure if the item has already been removed).
template<class T>
bool ListPairCell<T>::removeFromList(void)
{
   if(m_index == NULL || *m_index == NULL) return false;
   
   *m_index = NULL;
   m_index = NULL;

   // Delink from the list.
   if(m_next != NULL) m_next->setPrev(m_prev);
   else if(m_prev != NULL) m_prev->setNext(m_next);

   return true;
}

// --- Accessors
   
// getData(): This function is a mystery.
template<class T>
const T & ListPairCell<T>::getData(void) const
{
   return *m_data;
}

// getNext(): Gets the next element of the list.
template<class T>
ListPairCell<T> * ListPairCell<T>::getNext(void) const
{
   return m_next;
}

// getPrev(): Similar to getNext(), but backwards.
template<class T>
ListPairCell<T> * ListPairCell<T>::getPrev(void) const
{
   return m_prev;
}

// getIndex: Gets the contents of the index pointer of the cell.
//  Could be NULL if the cell has already been removed.
template<class T>
ListPairCell<T> ** ListPairCell<T>::getIndex(void) const
{
   return m_index;
}

#endif // __LISTPAIRCELL_CPP__
