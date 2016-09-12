#include <stdio.h>
#include <math.h>

#include "Game.h"
#include "SolutionPair.h"

// Our constructor initializes everything to empty.
Game::Game(int n)
{
   // Set the values of n and its derivatives.
   m_n = n;
   m_nn = n * m_n;
   m_nnn = n * m_nn;

   // Initialize our row, column and box indices.
   int row = 0;
   int col = 0;
   int box = 0;

   // Initialize our special counters for the box.
   int box_ctr1 = 0;
   int box_ctr2 = 0;
   int box_ctr3 = 0;

   // Allocate our rows, columns and boxes.
   m_rows = new Container * [m_nn];
   m_cols = new Container * [m_nn];
   m_boxes = new Container * [m_nn];

   for(int i = 0; i < m_nn; i++)
   {
      m_rows[i] = new Container(m_n);
      m_cols[i] = new Container(m_n);
      m_boxes[i] = new Container(m_n);
   }

   // Allocate this, too.
   m_remaining = new List<Cell *>;

   // Since this could be really huge, let's make sure we have the largest int
   //  we can reasonably make (this will be 64 bits on 64-bit systems where the
   //  compiler understands that it is, like say Linux on AMD64).
   unsigned long int cellcount = m_nnn * n;

   // This can get to be a lot of cells pretty quickly.
   m_cells = new Cell * [cellcount];

   for(unsigned long int i = 0; i < cellcount; i++)
   {
      m_cells[i] = new Cell(m_cols[col],
			    m_rows[row],
			    m_boxes[box],
			    m_remaining,
			    n);

      // If we've overflowed the columns, reset and go to the next row.
      if(++col == m_nn)
      {
	 // Reset the column.
	 col = 0;

	 // Next row.
	 row++;
      }

      // If we've overflowed our box counters, manage the boxes.
      if(++box_ctr1 == m_n)
      {
	 // Check to see if we're going to overflow the secondary counter.
	 if(++box_ctr2 == m_n)
	 {
	    // And now the tertiary counter.
	    if(++box_ctr3 == m_n)
	    {
	       // If so, next box.
	       box++;
	       box_ctr3 = 0;
	    } else {
	       // If not, go back (n - 1) boxes.
	       box -= (n - 1);
	    }
	    
	    box_ctr2 = 0;
	 } else {
	    // If not, just go to the next box.
	    box++;
	 }
	 
	 box_ctr1 = 0;
      }
   }
}

// Our method for setting the value of an individual cell.  Calculates the
//  appropriate cell to store into, which in turn has the proper row, column
//  and box stored inside it.  Returns the success of the operation.
bool Game::setCellValue(int x, int y, int value)
{
   // If it's zero, we silently ignore it.
   if(value == 0) return true;

   // However, if it's out of bounds, cry bloody murder.
   if(y >= m_nn || x >= m_nn || value > m_nn || value < 0) return false;

   // Calculate the index.
   unsigned long int cellindex = (y * m_nn) + x;

   List<SolutionPair *> *solvable, *rhs;

   solvable = m_cells[cellindex]->setValue(value);

   if(solvable == NULL) return false;

   while(solvable->getCount() > 0)
   {
      SolutionPair *sp = solvable->pop();

      Cell *toSolve = sp->cell;
      rhs = toSolve->setValue(sp->value);

      delete sp;

      if(rhs != NULL)
      {
	 solvable->splice(rhs);

	 delete rhs;
      } else {
	 delete solvable;
	 return false;
      }
   }

   return true;
}

// Gets the remaining count of cells from the board.
int Game::getRemainingCells(void) const
{
   return m_remaining->getCount();
}

// Prints out a textual representation of the board to the supplied file.
void Game::printBoard(FILE *output)
{
   // Initialize our overall index.
   unsigned long int index = 0;

   // Determine how wide our numbers will be.
   int num_width = (int)ceil(log10((double)m_nn));

   // Generate the format string.
   char *format;
   asprintf(&format, "%%%dd ", num_width);

   // Print a newline to start with.
   fprintf(output, "\n");
   
   for(int yi = 0; yi <= m_n; yi++)
   {
      // Draw a separator line.
      for(int i = 0; i < m_n; i++)
      {
	 fprintf(output, "+-");

	 for(int j = 0; j < m_n; j++)
	 {
	    for(int k = 0; k < num_width + 1; k++)
	    {
	       fprintf(output, "-");
	    }
	 }
      }

      // Terminate the line.
      fprintf(output, "+\n");

      // Breaks are ugly, but it beats another level of nesting.
      if(yi == m_n) break;

      for(int yj = 0; yj < m_n; yj++)
      {
	 for(int xi = 0; xi < m_n; xi++)
	 {
            // Start this box edge.
	    fprintf(output, "| ");

	    for(int xj = 0; xj < m_n; xj++)
	    {
	       fprintf(output, format, m_cells[index++]->getValue());
	    }
	 }

	 // Terminate this line.
	 fprintf(output, "|\n");
      }
   }

   fprintf(output, "\nRemaining cells: %d\n\n", getRemainingCells());
}
