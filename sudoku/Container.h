#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include <stdio.h>

#include "List.h"
#include "ListCell.h"
#include "ListPair.h"
#include "ListPairCell.h"
#include "Cell.h"
#include "SolutionPair.h"

class Container
{
   // Our list of cells in the container.
   List<class Cell *> m_cells;

   // The index that indicates how many cells we have added thus far.
   int m_index;

   // The size factor n of the container, plus n^2.
   int m_n, m_nn;

   // The array of ListPairs that hold the cells with available numbers.
   ListPair<class Cell *> **m_available;

   // Our ugly kludgy "occupied" flags.
   bool *m_occupied;

  public:

   // --- Constructors

   // We only need n to initialize this.
   Container(int n);

   
   // --- Mutators

   // Adds a cell to the list of cells, and enters it into the lists of number
   //  availability.  Returns the index of the cell in the lists.
   int addCell(class Cell *cell);

   // Removes a cell from the appropriate number list, given the index.  If any
   //  number lists have only one number in them, the appropriate cell is then
   //  solved.  Returns the overall success.
   List<SolutionPair *> * removeCellFromNumber(int index, int number);

   // Does the same as the above, only for all number lists.
   List<SolutionPair *> * removeCell(int index);

   // Clears the list of a given number and removes that number from the
   //  available numbers of any cells within said list.  This also solves any
   //  subsequent solvable cells it finds.
   List<SolutionPair *> * clearNumberList(int number);

   // Removes a cell from all the appropriate lists in the container.  Solves
   //  any solvable cells left over.
   List<SolutionPair *> * cellSolved(int index, int value);

   // A bit of a kludge, but necessary: sets the number specified in the
   //  container as "occupied" so that intermediate resolution processes won't
   //  spuriously resolve to a number we're trying to resolve around.
   void setOccupied(int number);
};

#endif // __CONTAINER_H__
