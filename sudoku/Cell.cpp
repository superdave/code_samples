#include <iostream>

#include "List.h"
#include "ListCell.h"
#include "ListPair.h"
#include "ListPairCell.h"
#include "Container.h"
#include "Cell.h"

// --- Constructors
   
// Nothing particularly special here, except for n.  Specify the N of your
//  puzzle with that.
Cell::Cell(Container *col,
	   Container *row,
	   Container *box,
	   List<Cell *> *list,
	   int n)
   : m_numbers(n * n, 0), m_value(0)
{
   m_col = col;
   m_row = row;
   m_box = box;
   m_list = list;

   m_col_addr = col->addCell(this);
   m_row_addr = row->addCell(this);
   m_box_addr = box->addCell(this);
   m_list_addr = list->addToBackOfList(this);

   int nn = n * n;

   for(int i = 0; i < nn; i++)
   {
      m_numbers.setData(i, i + 1);
   }
}

   
// --- Mutators

// Sets the value of the cell and removes it from the lists it's on,
//  removing the available numbers from the cells in its row, col and box.
//  Since the removal of available numbers can result in the solving of
//  cells, this returns a bool indicating overall success (i.e. any errors
//  in subsequent solving operations, etc. will be reported).
List<SolutionPair *> * Cell::setValue(int value)
{
   // First, check to make sure that a value has not already been assigned.
   if(m_value != 0 && m_value != value) return NULL;

   // Next, if we're trying to set our own value, we're done.
   if(value == 0 || m_value == value) return new List<SolutionPair *>;

   // Set our value.
   m_value = value;

   // Get rid of all the values from the number list.
   m_numbers.clear();

   List<SolutionPair *> *solvable = new List<SolutionPair *>;

   List<SolutionPair *> *rhs;

   // First, flag our current containers as having this number occupied.  Ugh.
   m_row->setOccupied(value);
   m_col->setOccupied(value);
   m_box->setOccupied(value);

   // Remove ourselves from our column, row and box.  And the global list.
   rhs = m_row->clearNumberList(value);
    
   if(rhs != NULL)
   {
      solvable->splice(rhs);

      delete rhs;
   } else {
      delete solvable;

      return NULL;
   }

   rhs = m_col->clearNumberList(value);
    
   if(rhs != NULL)
   {
      solvable->splice(rhs);

      delete rhs;
   } else {
      delete solvable;

      return NULL;
   }

   rhs = m_box->clearNumberList(value);
    
   if(rhs != NULL)
   {
      solvable->splice(rhs);

      delete rhs;
   } else {
      delete solvable;

      return NULL;
   }

   rhs = m_col->cellSolved(m_col_addr, value);

   if(!rhs)
   {
      delete solvable;

      return NULL;
   } else {
      solvable->splice(rhs);

      delete rhs;
   }

   rhs = m_row->cellSolved(m_row_addr, value);

   if(!rhs)
   {
      delete solvable;

      return NULL;
   } else {
      solvable->splice(rhs);

      delete rhs;
   }

   rhs = m_box->cellSolved(m_box_addr, value);

   if(!rhs)
   {
      delete solvable;

      return NULL;
   } else {
      solvable->splice(rhs);

      delete rhs;
   }


   m_list->removeFromList(m_list_addr);

/*   // Now go through the column, removing possible values.
   ListCell<Cell *> *i = m_col->getHead();
   while(i != NULL && m_col->getCount() != 0)
   {
      // Remove the possible value from the current cell.
      if(i->getData()->removePossibleValue(value) == false) return false;

      i = i->getNext();
   }
   
   // Now go through the row, removing possible values.
   i = m_row->getHead();
   while(i != NULL && m_row->getCount() != 0)
   {
      // Remove the possible value from the current cell.
      if(i->getData()->removePossibleValue(value) == false) return false;

      i = i->getNext();
   }
   
   // Now go through the box, removing possible values.
   i = m_box->getHead();
   while(i != NULL && m_box->getCount() != 0)
   {
      // Remove the possible value from the current cell.
      if(i->getData()->removePossibleValue(value) == false) return false;

      i = i->getNext();
   }
*/
   return solvable;
}
   
// Removes a possible value from the cell's list of available values.  If
//  only one possible value remains, calls setValue() with that value, which
//  sets the value of the cell and operates on the other collections of
//  values, possibly solving other cells in the process.  Returns a bool
//  indicating overall success (i.e. if any of the setValue() operations
//  return false, this will return false as well).
List<SolutionPair *> * Cell::removePossibleValue(int value)
{
   // If this value has already been removed, it's OK.
   m_numbers.removeCell(value - 1);

   List<SolutionPair *> *solvable = new List<SolutionPair *>;

   List<SolutionPair *> *rhs;

   rhs = m_row->removeCellFromNumber(m_row_addr, value);

   if(!rhs)
   {
      delete solvable;

      return NULL;
   } else {
      solvable->splice(rhs);

      delete rhs;
   }

   rhs = m_col->removeCellFromNumber(m_col_addr, value);

   if(!rhs)
   {
      delete solvable;

      return NULL;
   } else {
      solvable->splice(rhs);

      delete rhs;
   }

   rhs = m_box->removeCellFromNumber(m_box_addr, value);

   if(!rhs)
   {
      delete solvable;

      return NULL;
   } else {
      solvable->splice(rhs);

      delete rhs;
   }

   if(m_numbers.getRemaining() == 1)
   {
      int num = m_numbers.firstAvailable()->getData();

      SolutionPair *sp = new SolutionPair;

      sp->value = num;
      sp->cell = this;
      
      solvable->push(sp);
   }

   return solvable;
}

// If there is a single value left to take, sets the cell to it.  Returns
//  the queue of solvables, or NULL if it is unsolvable.
List<SolutionPair *> * Cell::solve(void)
{
   // See if we're trying to be re-solved.
   if(m_value != 0) return new List<SolutionPair *>;
   
   // Make sure we're actually solvable.
   if(m_numbers.getRemaining() != 1) return NULL;

   // Get our number.
   return setValue(m_numbers.firstAvailable()->getData());
}

   
// --- Accessors
   
// Gets the value of the cell.
int Cell::getValue(void) const
{
   return m_value;
}
