
#ifndef __LISTPAIR_H__
#define __LISTPAIR_H__

#include "ListPairCell.h"

template <class T>
class ListPair
{
   // The "ordered" list never has cells removed from it.  "Removed" cells from
   //  the "available" list are marked with a NULL in the pointer in this
   //  array, which is actually just an array of pointers into the "available"
   //  list.
   ListPairCell<T> **m_ordered;

   // The "available" list, on the other hand, is a dynamic doubly-linked list.
   //  When cells are removed from it, they are delinked and freed, and their
   //  siblings in the "ordered" list are marked with a NULL in the sibling
   //  pointer.  This list allows us to quickly scan the unused cells, which
   //  is especially nice when the list is nearly all used up.
   ListPairCell<T> *m_available;

   // The count of total items in the list.  Not used for much.
   int m_totalCount;

   // The count of available items in the list.  Used quite often.
   int m_size;

   // Our array of values.  This is stored only once, in the list, so that we
   //  don't duplicate the storage of what could potentially be large structs.
   T *m_data;

  public:

   // --- Constructors
   
   // The list is statically sized, since allowing for dynamic sizes would
   //  introduce pesky array reallocation when it got bigger.  And no one
   //  wants that.  Besides, for the application it's used for, we don't need
   //  dynamic list sizes.  One may optionally supply an object to be used
   //  as the initial value for the list items.
   ListPair(int size, T data = T());

   
   // --- Mutators
   
   // Removes a cell from the pairs of lists.  Accepts an in index into the
   //  ordered list.  Returns false if this index has already been removed,
   //  true otherwise.
   bool removeCell(int index);

   // Removes a cell from the pairs of lists.  Accepts the address of a cell
   //  within the list.
   bool removeCell(ListPairCell<T> *cell);

   // Sets data at the index specified.  Returns false if the value has already
   //  been removed.
   bool setData(int index, const T &value);
   
   // Clears all data from the list.
   void clear(void);

   // --- Accessors

   // Gets the overall size of the list.
   int getTotalCount(void) const;

   // Gets the remaining size of the list.
   int getRemaining(void) const;

   // Gets a pointer to the value at index supplied.  Returns NULL if the index
   //  is out of bounds.
   T * getData(int index);

   // Gets the first available list cell.
   ListPairCell<T> * firstAvailable(void);
};

#include "ListPair.cpp"

#endif // __ LISTPAIR_H__
