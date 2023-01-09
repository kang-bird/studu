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
  LIBS= -lgtest -lpthread -lrt -lm
  LEAKER= valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes -s --log-file=valgrind.txt
  LINUXFLAGS= -lpthread -lsubunit -ldl -lrt -lm
else
  LIBS= -lgtest
  LEAKER= CK_FORK=no leaks --atExit --
  LINUXFLAGS=
endif

all: clean build

install: uninstall
	mkdir ../build
	$(CC) $(SOURCES) -o ../build/MLP $(GTKFLAGS)
	
uninstall:
	rm -rf ../build

build:	clean
	$(CC) $(SOURCES) -o MLP $(GTKFLAGS) $(LINUXFLAGS) 

test_prep: $(TSOURCES)
	$(TCC) $(TSOURCES) $(LIBS) -o test $(GTKFLAGS)

test: test_prep
	./test

clean:
	@rm -f *.o test *.out *.gcov *.gcda *.gcno *.info *.a *.tar CPPLINT.cfg valgrind.txt MLP
	@rm -rf ./coverage ./info

rebuild: clean all

leaks: test_prep
	$(LEAKER) ./test

.PHONY: all install uninstall build test clean rebuild leaks test_prep
	$(LEAKER) ./test
