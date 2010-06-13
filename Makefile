# Makefile for 'fahrplanauskunft'
VERSION=2.0.0
CFLAGS=-g -Wall -O -lm
PROGRAM=fahrplanauskunft
CHECKSCRIPT=check.sh

all: ${PROGRAM} test-heap

${PROGRAM}: ${PROGRAM}.o
	gcc ${CFLAGS} -o ${PROGRAM} ${PROGRAM}.o

${PROGRAM}.o: ${PROGRAM}.c ${PROGRAM}.h heap.h types.h
	gcc ${CFLAGS} -c ${PROGRAM}.c

test-heap: test-heap.c heap.h
	gcc ${CFLAGS} -o test-heap test-heap.c
	
check: ${CHECKSCRIPT} ${PROGRAM}
	./${CHECKSCRIPT} ${PROGRAM}

clean:
	rm -f ./${PROGRAM}
	rm -f ./${PROGRAM}.o
	
dist: all distclean
	mkdir ../${PROGRAM}-${VERSION}/
	cp * ../${PROGRAM}-${VERSION}/
	tar cvzf ./${PROGRAM}-${VERSION}.tgz ../tron-${VERSION}
	rm -r ../${PROGRAM}-${VERSION}/

distclean:
	rm -f ./${PROGRAM}-${VERSION}.tgz
	rm -f ./*~
	rm -f ./${PROGRAM}.o

