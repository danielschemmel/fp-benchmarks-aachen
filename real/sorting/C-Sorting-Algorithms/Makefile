PROG=selectionSortTester
CC=gcc
CFLAGS=-std=c99
SRC=main.c selectionSort.c

.PHONY: all

all: ${PROG}

${PROG}: ${SRC}
	${CC} ${CFLAGS} ${SRC} -o ${PROG}
	
clean: 
	@if test -f ${PROG}; then rm ${PROG}; fi
