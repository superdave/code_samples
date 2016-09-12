Sudoku
======

This is the code implementation (and accompanying analysis doc) for my
undergraduate algorithms class from 2005, so the quality of both code and prose
do not necessarily reflect my current skill set (the code seems OK on some
inspection, but for some reason I have a mix of hard and soft tabs which ruins
the indentation).  I'd like to think this still reflects an understanding of
optimization especially as regards algorithmic complexity, even if it is rather
old.

The prompt for this assigment is (as of September 2016) still available on the
original course website [here][1].


Notes
=====

This implements a Sudoku solver (for any deterministically solvable Sudoku
puzzle, which is most if not all of them) in O(n^6) time, where n is equal to
the size of a box (for typical 9x9 Sudoku, for example, n = 3).  I believe that
O(n^6) is the fastest time to solve the puzzle deterministically, as there are
n^4 cells in the game, each with n^2 possible values.

The primary optimization in this solver is a list data structure that allows for
constant-time random access for removing possible matches in constant time,
while maintaining a traditional doubly-linked list for tracking the matches
still available (which allows for constant-time resolution of the final
available match once the list length gets down to 1).  Without this structure,
either the elimination of potential matches or the final resolution of the last
value would be O(n), which would make the algorithm take O(n^7).

Caveats
-------

If I were to implement this today, I probably would use something safer than C++
unless I absolutely needed the speed (and even then there are good compiled
languages like Rust that should be roughly equivalent in speed while providing
good memory safety).  Too many arbitrary length accesses for my comfort without
any compiler or runtime-enforced bounds checking.

It may be possible to solve Sudoku puzzles in less than O(n^6), but probably not
deterministically (which is what the assignment dictates).  This problem is
distantly related to the Secret Santa problem, though the parameters are quite
different in a lot of ways.

For some reason, if you do not specify an output file, the output puzzle is
printed to `stdout` twice.  Since this code is 11 years old and I haven't looked
closely at it again, I assume that's because it just blindly prints to both
`stdout`/`stderr` and the designated output file, which defaults to `stdout`.


[1]: http://www.csee.umbc.edu/~tadwhite/441.f05/project.html "project link"

