#include <stdio.h>

#include "Game.h"

void usage(void)
{
   fprintf(stderr, "Usage: sudoku <n> [infile [outfile]]\n\n");
   fprintf(stderr, "  Where: n = the size factor of the board\n");
   fprintf(stderr, "         infile = the optional input text filename\n");
   fprintf(stderr, "         outfile = the optional output filename\n\n");
}

int main(int argc, char **argv)
{
   // Predeclare our n variable, since C++ is lexically scoped.
   int n = 0;

   // Also predeclare our input file.
   FILE *input = stdin;
   FILE *output = stdout;

   // Do different things, depending on usage.
   switch(argc)
   {
      case 0:
      case 1:
	 // If no args (argc = 0 should be impossible anyway), print usage.
	 usage();
	 return -1;

      case 4:
	 // If we have four args, the last is our outfile name.  Open it.
	 if(NULL == (output = fopen(argv[3], "wb")))
	 {
	    // If there was an error, display it.
	    char *str = NULL;
	    asprintf(&str, "Error opening output file \"%s\"", argv[3]);
	    perror(str);
	    return -2;
	 }

      case 3:
	 // If we have three args, the last is our infile name.  Open it.
	 if(NULL == (input = fopen(argv[2], "rb")))
	 {
	    // If there was an error, display it.
	    char *str = NULL;
	    asprintf(&str, "Error opening input file \"%s\"", argv[2]);
	    perror(str);
	    return -2;
	 }

	 // Otherwise, proceed onto getting n.
      case 2:
	 // Get n.
	 n = atoi(argv[1]);
	 break;
   }

   // Create our game.
   Game game(n);

   // Scan for our values.
   int x = 1, y = 1, val;

   // If we're doing this interactively, parse the commandline until we die.
   while(!feof(input) && game.getRemainingCells() != 0)
   {
      // We only want to print out each iteration of the board if the user is
      //  in interactive mode or if the output is going to a file.  Otherwise
      //  it wastes a lot of time printing to the screen.
      if(input == stdin || output != stdout)
      {
	 game.printBoard(output);
      }

      if(input == stdin)
      {
	 fprintf(stderr, "Enter move (format: \"x y value\", ^D to end): ");

	 while(!fscanf(input, "%d", &x));
	 while(!fscanf(input, "%d", &y));
      }

      while(!fscanf(input, "%d", &val));

      // How ugly!
      if(feof(input)) break;

      bool success = game.setCellValue(x - 1, y - 1, val);

      if(!success)
      {
	 if(output != stdout)
	 {
	    fprintf(stderr,
		    "Error: bad placement of a number: x=%d y=%d val=%d.\n",
		    x,
		    y,
		    val);
	 }

	 fprintf(output,
		 "Error: bad placement of a number: x=%d y=%d val=%d.\n",
		 x,
		 y,
		 val);
	 return -4;
      }

      if(input != stdin)
      {
	 if(++x > n * n)
	 {
	    y++;
	    x = 1;
	 }
      }
   }

   game.printBoard(output);

   if(game.getRemainingCells() == 0)
   {
      game.printBoard(stderr);

      if(output != stdout)
      {
	 fprintf(stderr, "Finished game!\n");
      }

      fprintf(output, "Finished game!\n");
   } else {
      if(output != stdout)
      {
	 fprintf(stderr, "Did not finish game.\n");
      }

      fprintf(output, "Did not finish game.\n");
   }
   
   return 0;
}
