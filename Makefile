# Makefile for 'fahrplanauskunft'
VERSION=1.0.97
CFLAGS=-g -Wall -O
PROGRAM=fahrplanauskunft
CHECKSCRIPT=check.sh

all: ${PROGRAM} test-heap

${PROGRAM}: ${PROGRAM}.o
	gcc ${CFLAGS} -o ${PROGRAM} ${PROGRAM}.o

${PROGRAM}.o: ${PROGRAM}.c ${PROGRAM}.h heap.h types.h prioritysearch.h
	gcc ${CFLAGS} -c ${PROGRAM}.c

#test-heap: test-heap.c heap.h
#	gcc ${CFLAGS} -o test-heap test-heap.c
	
check: ${CHECKSCRIPT} ${PROGRAM}
	./${CHECKSCRIPT} ${PROGRAM}

checkall: testall.sh
	./testall.sh

clean:
	rm -f ./${PROGRAM}
	rm -f ./${PROGRAM}.o
	rm -f ./test-heap
	
dist: ${PROGRAM} distclean
	mkdir ../${PROGRAM}-${VERSION}/
	cp * ../${PROGRAM}-${VERSION}/
	tar cvzf ./${PROGRAM}-${VERSION}.tgz ../${PROGRAM}-${VERSION}
	rm -r ../${PROGRAM}-${VERSION}/

distclean:
	rm -f ./${PROGRAM}-${VERSION}.tgz
	rm -f ./*~
	rm -f ./${PROGRAM}.o

