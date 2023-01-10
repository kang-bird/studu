SOURCES = general/data_base_class.cc\
	general/file_reader.cc\
	general/types.cc\

ASOURCES = main.cc\
	interface/interface.cc\

TREESOURCES = AVL/self_balancing_binary_search_tree.cc\
	hash_table/hash_table.cc

CC = g++ -std=c++17 -Wall -Werror -Wextra
GFLAGS= -fprofile-arcs -ftest-coverage
OS=$(shell uname)

ifeq ($(OS), Linux)
  LIBS = -lpthread -lsubunit -ldl -lrt -lm
  LEAKER = valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes -s --log-file=valgrind.txt
else
  LIBS = 
  LEAKER = CK_FORK=no leaks --atExit --
endif

all: build
	./treeandhash.out

build: clean
	$(CC) $(ASOURCES) $(SOURCES) $(TREESOURCES) $(LIBS) -o treeandhash.out


test: clean
	$(CC) tests.cc $(SOURCES) $(TREESOURCES) -lgtest $(LIBS) -o test.out
	./test.out

gcov_report:
	@rm -rf coverage test *.info *.gcda *.gcno
	@$ $(CC) tests.cc $(SOURCES) $(TREESOURCES) -lgtest $(LIBS) $(GFLAGS) -o test.out
	@./test.out
	@lcov -c -d ./ --no-external -o coverage.info
	@genhtml -o coverage coverage.info
	@rm -f *.gcno *gcda *.info *.o
	@open coverage/index.html


clean:
	@rm -f *.o *.a treeandhash.out test.out
	@rm -rf ./coverage
	@rm -f *.gcno *gcda *.info *.o
	@rm -f *.dot

rebuild: clean all

check: cppcheck

leaks: test
	$(LEAKER) ./test.out

.PHONY: all build clean rebuild test leaks gcov_report