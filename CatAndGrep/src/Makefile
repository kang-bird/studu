CC= gcc

all: cat grep

cat: cat/cat.c
	rm -rf cat/cat
	$(CC) cat/cat.c -o cat/cat
	
grep: grep/grep.c
	rm -rf grep/grep
	$(CC) grep/grep.c -o grep/grep

clean:
	cd cat
	rm -rf cat/*.o cat/libcat.a cat/cat.a cat/cat
	rm -rf grep/*.o grep/libgrep.a grep/grep.a grep/grep

rebuild: clean all

r: clean all

.PHONY: cat grep clean rebuild r all