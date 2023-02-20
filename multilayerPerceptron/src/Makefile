SOURCES= main.cpp\
	 viewer/viewer.cpp\
	 controller/controller.cpp\
	 model/graph_model/graph_model.cpp\
	 model/matrix_model/matrix_model.cpp\
	 model/matrix_model/matrix.cpp\
	 types.cpp
	 
TSOURCES= test.cpp\
	 controller/controller.cpp\
	 model/graph_model/graph_model.cpp\
	 model/matrix_model/matrix_model.cpp\
	 model/matrix_model/matrix.cpp\
	 types.cpp

CC=clang++ -std=c++17
TCC=g++ -std=c++17
GTKFLAGS= `pkg-config gtkmm-4.0 --libs --cflags`
GFLAGS= -fprofile-arcs -ftest-coverage
OS=$(shell uname)

ifeq ($(OS), Linux)
  LEAKER= valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes -s --log-file=valgrind.txt
  LIBS= -lpthread -lsubunit -ldl -lrt -lm
else
  LEAKER= CK_FORK=no leaks --atExit --
  LIBS=
endif

all: clean build


build:	clean
	$(CC) $(SOURCES) -o AI $(GTKFLAGS) $(LIBS) 

test_prep: $(TSOURCES)
	$(TCC) $(TSOURCES) -lgtest -o test $(GTKFLAGS) $(LIBS)

test: test_prep
	./test

clean:
	@rm -f *.o test *.out *.a valgrind.txt AI .temp.csv

rebuild: clean all

leaks: test_prep
	$(LEAKER) ./test

.PHONY: all install uninstall build test clean rebuild leaks test_prep
	$(LEAKER) ./test
