#ifndef __LIST_CPP__
#define __LIST_CPP__

#include "List.h"

// --- Constructors / Destructors
   
// No arguments need to be supplied.  Isn't that nice?
template <class T>
List<T>::List(void)
   : m_size(0), m_head(NULL), m_tail(NULL)
{
   // Nothing here.
}

template <class T>
List<T>::~List(void)
{
   while(m_size > 0)
   {
      removeFromList(m_head);
   }
}

// --- Mutators
   
// Removes the item from the list.  Technically, one could just call the
//  method directly on the list cell object, which is what this does, but
//  that wouldn't update the list count, which would cause problems.
template <class T>
void List<T>::removeFromList(ListCell<T> *obj)
{
   // Make sure we're not doing something dumb.
   if(obj == NULL) return;

   m_size--;

   // Check to see if we're removing the head or tail object (or both).
   if(m_head == obj)
   {
      m_head = obj->getNext();
   }

   if(m_tail == obj)
   {
      m_tail = obj->getPrev();
   }

   obj->removeFromList();

   delete obj;
}

// Adds an item to the list and returns a pointer to the cell for use later.
//  Stores on the front of the list.
template <class T>
ListCell<T> * List<T>::addToFrontOfList(const T &data)
{
   ListCell<T> *cell = new ListCell<T>(m_head, NULL, data);

   m_head = cell;

   if(m_tail == NULL) m_tail = m_head;

   m_size++;

   return cell;
}

// Adds an item to the list and returns a pointer to the cell for use later.
//  Stores on the back of the list.
template <class T>
ListCell<T> * List<T>::addToBackOfList(const T &data)
{
   ListCell<T> *cell = new ListCell<T> (NULL, m_tail, data);

   m_tail = cell;

   if(m_head == NULL) m_head = m_tail;

   m_size++;

   return cell;
}

// Basically just an alias for addToFrontOfList().
template <class T>
ListCell<T> * List<T>::push(const T &data)
{
   return addToFrontOfList(data);
}

// Removes the head element and returns its data value.
template <class T>
const T List<T>::pop(void)
{
   if(m_head == NULL) return T();

   T data = m_head->getData();

   removeFromList(m_head);

   return data;
}

// Adds the contents of the lists together.
template <class T>
void List<T>::splice(List<T> *rhs)
{
   if(rhs == NULL) return;

   for(ListCell<T> *i = rhs->getHead();
       i != NULL;
       i = i->getNext())
   {
      addToBackOfList(i->getData());
   }
}


// --- Accessors

// Gets the head of the list.
template <class T>
ListCell<T> * List<T>::getHead(void) const
{
   return m_head;
}

// Gets the tail of the list.
template <class T>
ListCell<T> * List<T>::getTail(void) const
{
   return m_tail;
}

// Gets the current size of the list.
template<class T>
int List<T>::getCount(void) const
{
   return m_size;
}

#endif // __LIST_CPP__
