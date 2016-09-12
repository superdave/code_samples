#include <stdio.h>

#include "Container.h"

// --- Constructors

// We only need n to initialize this.
Container::Container(int n)
{
   m_n = n;
   m_nn = n * n;

   m_index = 0;

   m_available = new ListPair<Cell *> * [m_nn];

   m_occupied = new bool[m_nn];

   for(int i = 0; i < m_nn; i++)
   {
      m_occupied[i] = false;
   }

   // Generate our number lists with NULL cell addresses within them.
   for(int i = 0; i < m_nn; i++)
   {
      m_available[i] = new ListPair<Cell *>(m_nn, (Cell *)0xDEADBEEF);
   }
}
   
// --- Mutators

// Adds a cell to the list of cells, and enters it into the lists of number
//  availability.  Returns the index of the cell in the lists.
int Container::addCell(Cell *cell)
{
   if(m_index >= (m_nn)) return -1;

   m_cells.addToBackOfList(cell);

   for(int i = 0; i < m_nn; i++)
   {
      m_available[i]->setData(m_index, cell);
   }

   return m_index++;
}   

// Removes a cell from the appropriate number list, given the index.  If any
//  number lists have only one number in them, the appropriate cell is then
//  solved.  Returns the overall success.
List<SolutionPair *> * Container::removeCellFromNumber(int index, int number)
{
   if(number > m_nn || number <= 0) return NULL;

   List<SolutionPair *> *solvable = new List<SolutionPair *>;

   m_available[number - 1]->removeCell(index);

   if(m_available[number - 1]->getRemaining() == 1 && !m_occupied[number - 1])
   {
      ListPairCell<Cell *> *c = m_available[number - 1]->firstAvailable();

      Cell *toSolve = c->getData();

//      m_available[number - 1]->clear();

      SolutionPair *sp = new SolutionPair;

      sp->value = number;
      sp->cell = toSolve;

      solvable->push(sp);
   }

   return solvable;
}

// Does the same as the above, only for all number lists.
List<SolutionPair *> * Container::removeCell(int index)
{
   List<SolutionPair *> *solvable = new List<SolutionPair *>;
   
   for(int i = 1; i <= m_nn; i++)
   {
      List<SolutionPair *> *rhs = removeCellFromNumber(index, i);

      if(rhs != NULL)
      {
	 solvable->splice(rhs);

	 delete rhs;
      } else {
	 delete solvable;

	 return NULL;
      }
   }

   return solvable;
}


// Clears the list of a given number and removes that number from the
//  available numbers of any cells within said list.  This will queue up any
//  cells that it finds to be solvable and returns the queue upon completion.
List<SolutionPair *> * Container::clearNumberList(int number)
{
   List<SolutionPair *> *solvable = new List<SolutionPair *>;

   List<Cell *> *toCheck = new List<Cell *>;

   for(ListPairCell<Cell *> *i = m_available[number - 1]->firstAvailable();
       i != NULL;)
   {
      ListPairCell<Cell *> *next = i->getNext();

      toCheck->push(i->getData());

      m_available[number - 1]->removeCell(i);

      i = next;
   }

   // Check on all the cells that were in that batch.
   while(toCheck->getCount() > 0)
   {
      Cell *toReduce = toCheck->pop();

      List<SolutionPair *> *rhs = toReduce->removePossibleValue(number);

      if(rhs != NULL)
      {
	 solvable->splice(rhs);

	 delete rhs;
      } else {
	 delete solvable;
	 return NULL;
      }
   }

   return solvable;
}

// Removes a cell from all the appropriate lists in the container.  Solves
//  any solvable cells left over.
List<SolutionPair *> * Container::cellSolved(int index, int value)
{
   // Make sure there is a slot for this number in this container.  If not,
   //  return an error.
   //if(m_available[value - 1]->getRemaining() < 1) return false;

   List<SolutionPair *> *solvable = new List<SolutionPair *>;   

   List<SolutionPair *> *rhs;

   rhs = removeCell(index);

   if(rhs != NULL)
   {
      solvable->splice(rhs);

      delete rhs;
   } else {
      delete solvable;

      return NULL;
   }

   return solvable;
}

// A bit of a kludge, but necessary: sets the number specified in the
//  container as "occupied" so that intermediate resolution processes won't
//  spuriously resolve to a number we're trying to resolve around.
void Container::setOccupied(int number)
{
   m_occupied[number - 1] =  true;
}
