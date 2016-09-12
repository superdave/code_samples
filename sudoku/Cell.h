#ifndef __CELL_H__
#define __CELL_H__

#include <stdio.h>

#include "List.h"
#include "ListCell.h"
#include "ListPair.h"
#include "ListPairCell.h"
#include "Container.h"
#include "SolutionPair.h"

class Cell
{
   // Our column.
   class Container *m_col;

   // Our location within the column.
   int m_col_addr;


   // Our row.
   class Container *m_row;
   
   // Our location within the row.
   int m_row_addr;


   // Our box.
   class Container *m_box;

   // Our location within the box.
   int m_box_addr;


   // Our global list of cells.
   List<Cell *> *m_list;

   // Our position in said list.
   ListCell<Cell *> *m_list_addr;


   // Our list of available numbers.
   ListPair<int> m_numbers;


   // And, of course, our value.
   int m_value;
  
  public:
   
   // --- Constructors
   
   // Nothing particularly special here, except for n.  Specify the N of your
   //  puzzle with that.
   Cell(Container *col,
	Container *row,
	Container *box,
	List<Cell *> *list,
	int n);

   
   // --- Mutators

   // Sets the value of the cell and removes it from the lists it's on,
   //  removing the available numbers from the cells in its row, col and box.
   //  Since the removal of available numbers can result in the solving of
   //  cells, this returns a bool indicating overall success (i.e. any errors
   //  in subsequent solving operations, etc. will be reported).
   List<SolutionPair *> * setValue(int value);

   // Removes a possible value from the cell's list of available values.  If
   //  only one possible value remains, calls setValue() with that value, which
   //  sets the value of the cell and operates on the other collections of
   //  values, possibly solving other cells in the process.  Returns a bool
   //  indicating overall success (i.e. if any of the setValue() operations
   //  return false, this will return false as well).
   List<SolutionPair *> * removePossibleValue(int value);

   // If there is a single value left to take, sets the cell to it.  Returns
   //  the queue of solvables, or NULL if it is unsolvable.
   List<SolutionPair *> * solve(void);

   
   // --- Accessors
   
   // Gets the value of the cell.
   int getValue(void) const;
};

#endif // __CELL_H__
