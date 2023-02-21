CC= gcc
OS=$(shell uname)
ifeq ($(OS), Linux)
  LEAKER=valgrind --track-origins=yes --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose
else
  LEAKER=leaks --atExit --
endif

all: cat check test

cat: cat.c
	rm -rf cat
	$(CC) cat.c -o cat

clean:
	rm -rf *.o libcat.a cat.a cat cat.txt cat.txt result.txt

rebuild: clean all

r: clean all

leaks:
	CK_FORK=no $(LEAKER) ./cat -benst Makefile

.PHONY: cat clean rebuild r leaks all
