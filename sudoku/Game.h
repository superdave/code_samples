#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>

#include "List.h"
#include "ListCell.h"
#include "Cell.h"

class Game
{
   // The size of our game, along with the squared and cubed values.
   int m_n, m_nn, m_nnn;

   // Our cells.
   Cell **m_cells;

   // Our rows, columns and boxes.
   Container **m_rows, **m_cols, **m_boxes;

   // Our remaining cells.
   List<Cell *> *m_remaining;

  public:
   // Our constructor initializes everything to empty.
   Game(int n);

   // Our method for setting the value of an individual cell.  Calculates the
   //  appropriate cell to store into, which in turn has the proper row, column
   //  and box stored inside it.  Returns the success of the operation.
   bool setCellValue(int x, int y, int value);

   // Gets the remaining count of cells from the board.
   int getRemainingCells(void) const;

   // Prints out a textual representation of the board to the supplied file.
   void printBoard(FILE *output = stdout);
};

#endif // __GAME_H__
