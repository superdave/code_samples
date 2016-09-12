#ifndef __LISTCELL_CPP__
#define __LISTCELL_CPP__

#include "ListCell.h"

// The constructor takes a link to both sides of it and a pointer to its
//  data area.
template <class T>
ListCell<T>::ListCell(ListCell<T> *next, ListCell<T> *prev, T data)
   : m_next(NULL), m_prev(NULL)
{
   setNext(next);
   setPrev(prev);

   setData(data);
}

// --- Mutators

// setData(): Sets the internal data of the cell (and its sibling) to the
//  supplied data.
template <class T>
void ListCell<T>::setData(T data)
{
   m_data = data;
}

// setNext(): Sets the next element of the cell to be the supplied element,
//  and sets that element's previous to this one (if it's not set already).
template <class T>
void ListCell<T>::setNext(ListCell<T> *next)
{
   m_next = next;

   if(next != NULL && next->getPrev() != this) next->setPrev(this);
}

// setPrev(): Similar to setNext(), but backwards.
template <class T>
void ListCell<T>::setPrev(ListCell<T> *prev)
{
   m_prev = prev;

   if(prev != NULL && prev->getNext() != this) prev->setNext(this);
}

// Removes this cell from the current list
template <class T>
void ListCell<T>::removeFromList(void)
{
   // Delink from the list.
   if(m_next != NULL)
   {
      m_next->setPrev(m_prev);
   } else if(m_prev != NULL) {
      m_prev->setNext(m_next);
   }

   setNext(NULL);
   setPrev(NULL);
}
   

// --- Accessors
   
// getData(): This function is a mystery.
template <class T>
const T & ListCell<T>::getData(void) const
{
   return m_data;
}

// getNext(): Gets the next element of the list.
template <class T>
ListCell<T> * ListCell<T>::getNext(void) const
{
   return m_next;
}

// getPrev(): Similar to getNext(), but backwards.
template <class T>
ListCell<T> * ListCell<T>::getPrev(void) const
{
   return m_prev;
}

#endif // __LISTCELL_CPP__
