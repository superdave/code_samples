#ifndef __LISTPAIR_CPP__
#define __LISTPAIR_CPP__

#include <stdio.h>

#include "ListPair.h"
#include "ListPairCell.h"

// --- Constructors
   
// The list is statically sized, since allowing for dynamic sizes would
//  introduce pesky array reallocation when it got bigger.  And no one
//  wants that.  Besides, for the application it's used for, we don't need
//  dynamic list sizes.  One may optionally supply an object to be used
//  as the initial value for the list items.
template <class T>
ListPair<T>::ListPair(int size, T data)
{
   // Allocate the initial data.
   m_data = new T[size];

   // Initialize it.
   for(int i = 0; i < size; i++)
   {
      m_data[i] = T(data);
   }

   // Allocate the indices.
   m_ordered = new ListPairCell<T> * [size];

   // Initialize the available list to be empty.
   m_available = NULL;

   // Generate the list cells.
   for(int i = 0; i < size; i++)
   {
      m_available = new ListPairCell<T>(m_available,
					NULL,
					&m_ordered[i],
					&m_data[i]);
   }

   // Set the size trackers of the list.
   m_totalCount = m_size = size;
}
   
// --- Mutators
   
// Removes a cell from the pairs of lists.  Accepts an in index into the
//  ordered list.  Returns false if this index has already been removed,
//  true otherwise.
template <class T>
bool ListPair<T>::removeCell(int index)
{
   // Make sure we're in bounds.
   if(index >= m_totalCount) return false;

   // Delegate!
   return removeCell(m_ordered[index]);
}

// Removes a cell from the pairs of lists.  Accepts the address of a cell
//  within the list.
template <class T>
bool ListPair<T>::removeCell(ListPairCell<T> *cell)
{
   // Make sure we're not doing something silly.
   if(cell == NULL) return false;

   // Decrement the tracker.
   m_size--;

   // If we're out of stuff, make sure to clear the available pointer.
   if(m_size == 0)
   {
      m_available = NULL;
   } else if(cell == m_available) {
      // Or, if we're about to remove the first cell, make sure we set the
      //  head address.
      m_available = cell->getNext();
   }
   
   return cell->removeFromList();
}

// Sets data at the index specified.  Returns false if the value has already
//  been removed.
template <class T>
bool ListPair<T>::setData(int index, const T &value)
{
   if(index >= m_totalCount || m_ordered[index] == NULL) return false;

   m_data[index] = value;

   return true;
}

// Clears all data from the list.
template <class T>
void ListPair<T>::clear(void)
{
   for(ListPairCell<T> *i = firstAvailable();
       i != NULL;
       i = firstAvailable())
   {
      removeCell(i);
   }
}
   
// --- Accessors

// Gets the overall size of the list.
template <class T>
int ListPair<T>::getTotalCount(void) const
{
   return m_totalCount;
}

// Gets the remaining size of the list.
template <class T>
int ListPair<T>::getRemaining(void) const
{
   return m_size;
}

// Gets a pointer to the value at index supplied.  Returns NULL if the index
//  is out of bounds.
template <class T>
T * ListPair<T>::getData(int index)
{
   return &m_data[index];
}

// Gets the first available list cell.
template <class T>
ListPairCell<T> * ListPair<T>::firstAvailable(void)
{
   return m_available;
}

#endif // __LISTPAIR_CPP__
