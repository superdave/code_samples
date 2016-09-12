# Object files for the project.
OBJECTS = Cell.o Container.o Game.o sudoku.o

# Files to compile but not link in for this project.
OBJECTS_COMPILE = $(OBJECTS) List.o ListCell.o ListPair.o ListPairCell.o

# Our executable name.
TARGET = sudoku

# Flags for the compiler.
CXXFLAGS = -Werror -Wall -ansi -g

# Flags used only for linking (we need to link the math library for ceil() and
#  log()).
LDFLAGS = -lm

$(TARGET): $(OBJECTS_COMPILE)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $(TARGET)

# One clean to remove the object files and executables...
clean:
	rm -f $(OBJECTS_COMPILE) $(TARGET)

# And one to remove any editor backups, core dumps, etc.
cleanest: clean
	rm -f "*#" *~ core