# Makefile for tron
VERSION=2.0.0
CFLAGS=-g -Wall -O
PROGRAM=fahrplanauskunft
CHECKFAILURESCRIPT=checkfailure.sh

all: ${PROGRAM}

${PROGRAM}: ${PROGRAM}.o
	gcc ${CFLAGS} -o ${PROGRAM} ${PROGRAM}.o

${PROGRAM}.o: ${PROGRAM}.c ${PROGRAM}.h heap.h
	gcc ${CFLAGS} -c ${PROGRAM}.c
	
check: check1 check2

check1:
	./${CHECKFAILURESCRIPT} ${PROGRAM}
	
check2:
	./${PROGRAM} ubahn.txt > /dev/null

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

