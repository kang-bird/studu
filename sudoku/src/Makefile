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
	$(LEAKER) ./sudoku.out ..1.....5 ..7..3... 2..9..41. 1..4..26. ......8.. .4..9.... ...6....8 5.......9 ..2.7.63.

.PHONY: all build clean rebuild leaks gcov_report
