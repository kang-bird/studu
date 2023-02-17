OS := $(shell uname -s)

SOURCES= array.cpp\
		list.cpp\
		queue.cpp\
		stack.cpp\
		vector.cpp\
		map.cpp\
		set.cpp\
		multiset.cpp

CC=g++
GFLAGS= -fprofile-arcs -ftest-coverage
OS=$(shell uname)

ifeq ($(OS), Linux)
  LIBS= -lgtest -lpthread -lrt -lm
  LEAKER= valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes -s
  TESTGCC=-std=c++2a
else
  LIBS= -lgtest
  LEAKER= CK_FORK=no leaks --atExit --
  TESTGCC=-std=c++20
endif

all: test

test: $(SOURCES)
	$(CC) $(TESTGCC) -c test.cpp
	$(CC) test.o $(LIBS) -o Test
	./Test

gcov_report:
	@rm -rf coverage test *.info *.gcda *.gcno
	@$(CC)  $(TESTGCC) test.cpp  $(SOURCES) $(LIBS) $(GFLAGS) -o test
	@./test
	@lcov -c -d ./ -o coverage.info
	@genhtml -o coverage coverage.info
	@rm -f *.gcno *gcda *.info *.o
	

clean:
	@rm -f *.o Test *.out *.gcov *.gcda *.gcno *.info *.a CPPLINT.cfg
	@rm -rf ./coverage

rebuild: clean all

leaks: test
	$(LEAKER) ./Test

.PHONY: all clean rebuild test gcov_report leaks
