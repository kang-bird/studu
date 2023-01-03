OS := $(shell uname -s)
ifeq ($(OS), Linux)
  LIBS=-lcheck -lpthread -lrt -lm -lsubunit 
else
  LIBS=-lcheck
endif
GFLAGS= -fprofile-arcs -ftest-coverage
all: clean bit96.a test

test: bit96.a test.o
	gcc test.o -L. bit96.a $(LIBS) -o Test
	./Test

gcov_report: bit96.a
	rm -rf coverage test *.info *.gcda *.gcno
	gcc $(GFLAGS) -o Test test.c bit96.c arithmetic.c convertors.c comparison_operators.c another_functions.c -L. bit96.a $(LIBS)
	./Test
	lcov -c -d . -o coverage.info
	genhtml coverage.info -o coverage
	
test.o: test.c
	gcc -c test.c -o test.o

bit96.o: bit96.c bit96.h
	gcc -c bit96.c -o bit96.o

arithmetic.o: arithmetic.c bit96.h
	gcc -c arithmetic.c -o arithmetic.o 

convertors.o: convertors.c bit96.h
	gcc -c convertors.c -o convertors.o 

comparison_operators.o: comparison_operators.c bit96.h
	gcc -c comparison_operators.c -o comparison_operators.o 

another_functions.o: another_functions.c bit96.h
	gcc -c another_functions.c -o another_functions.o

clean:
	rm -f *.o Test *.out *.gcov *.gcda *.gcno *.info *.a
	rm -rf ./coverage

rebuild: clean all

bit96.a: bit96.o arithmetic.o convertors.o comparison_operators.o another_functions.o
	rm -rf bit96.a
	ar cr bit96.a bit96.o arithmetic.o convertors.o comparison_operators.o another_functions.o
	ranlib bit96.a
