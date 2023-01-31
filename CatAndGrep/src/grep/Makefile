CC= gcc
OS=$(shell uname)
ifeq ($(OS), Linux)
  LEAKER=valgrind --track-origins=yes --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
else
  LEAKER=leaks --atExit --
endif

all: grep check test

grep: grep.c
	rm -rf grep
	$(CC) grep.c -o grep

clean:
	rm -rf *.o libgrep.a grep.a test grep grep.txt grep.txt result.txt

rebuild: clean all

r: clean all

leaks:
	CK_FORK=no $(LEAKER) ./grep

.PHONY: cat grep clean rebuild r test leaks all
