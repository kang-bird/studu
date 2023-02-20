OS=$(shell uname)

ifeq ($(OS), Linux)
  LEAKER = valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes -s --log-file=valgrind.txt
else
  LEAKER = CK_FORK=no leaks --atExit --
endif

all:
	gcc -Wall -Werror -Wextra -o sudoku.out *.c

clean:
	rm -rf sudoku.out

rebuild: clean all

leaks: all
	$(LEAKER) ./sudoku.out 
	clean

.PHONY: all build clean rebuild leaks gcov_report
