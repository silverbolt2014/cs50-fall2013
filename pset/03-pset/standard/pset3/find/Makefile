#
# Makefile
#
# Computer Science 50
# Problem Set 3
#

all: find generate

find: find.c helpers.c helpers.h
	gcc -I ~/cs50-fall2013/cs50lib -ggdb3 -O0 -std=c99 -Wall -Werror -o find find.c helpers.c ~/cs50-fall2013/cs50lib/cs50.c -lm

generate: generate.c
	gcc -I ~/cs50-fall2013/cs50lib -ggdb3 -O0 -std=c99 -Wall -Werror -o generate generate.c

clean:
	rm -f *.o a.out core find generate
