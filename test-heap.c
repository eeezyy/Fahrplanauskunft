#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "heap.h"

// empty heap, adding one node
int test1() {
	heapnode **heap1 = (heapnode **)malloc(sizeof(heapnode *));
	station *st1 = (station *)malloc(sizeof(station));
	st1->lengthSum = 1;
	heapNodeInsert(heap1, st1);
	if(heap1==NULL) return 0;
	if((*heap1)->halt==NULL) return 0;
	return 1;
}

// adding equal number
// checking remove
int test2() {
	heapnode **heap1 = (heapnode **)malloc(sizeof(heapnode *));
	station *st1 = (station *)malloc(sizeof(station));
	strcpy(st1->name,"Node1");
	st1->lengthSum = 3;
	station *st2 = (station *)malloc(sizeof(station));
	strcpy(st2->name,"Node2");
	st2->lengthSum = 3;
	heapNodeInsert(heap1, st1);
	heapNodeInsert(heap1, st2);
	heapNodeRemove(heap1);
	heapNodeRemove(heap1);
	if(heap1==NULL) return 0;
	if((*heap1)!=NULL) return 0;
	return 1;
}

// adding smaller, then bigger node
// checkin remove
int test3() {
	heapnode **heap1 = (heapnode **)malloc(sizeof(heapnode *));
	station *st1 = (station *)malloc(sizeof(station));
	strcpy(st1->name,"Node1");
	st1->lengthSum = 3;
	station *st2 = (station *)malloc(sizeof(station));
	strcpy(st2->name,"Node2");
	st2->lengthSum = 5;
	heapNodeInsert(heap1, st1);
	heapNodeInsert(heap1, st2);
	if(heapNodeRemove(heap1)->lengthSum!=3) return 0;
	if(heapNodeRemove(heap1)->lengthSum!=5) return 0;
	if(heap1==NULL) return 0;
	if((*heap1)!=NULL) return 0;
	return 1;
}

// adding bigger, then smaller node
// checkin remove
int test4() {
	heapnode **heap1 = (heapnode **)malloc(sizeof(heapnode *));
	station *st1 = (station *)malloc(sizeof(station));
	strcpy(st1->name,"Node1");
	st1->lengthSum = 5;
	station *st2 = (station *)malloc(sizeof(station));
	strcpy(st2->name,"Node2");
	st2->lengthSum = 3;
	heapNodeInsert(heap1, st1);
	heapNodeInsert(heap1, st2);
	if(heapNodeRemove(heap1)->lengthSum!=3) return 0;
	if(heapNodeRemove(heap1)->lengthSum!=5) return 0;
	if(heap1==NULL) return 0;
	if((*heap1)!=NULL) return 0;
	return 1;
}

// adding three stations with different length
// testing heapNodeChange of the middle length
// checkin remove
int test5() {
	heapnode **heap1 = (heapnode **)malloc(sizeof(heapnode *));
	//*heap1 = (heapnode *)malloc(sizeof(heapnode));
	station *st1 = (station *)malloc(sizeof(station));
	strcpy(st1->name,"Node1");
	st1->lengthSum = 5;
	station *st2 = (station *)malloc(sizeof(station));
	strcpy(st2->name,"Node2");
	st2->lengthSum = 3;
	station *st3 = (station *)malloc(sizeof(station));
	strcpy(st3->name,"Node3");
	st3->lengthSum = 1;
	heapNodeInsert(heap1, st1);
	heapNodeInsert(heap1, st2);
	heapNodeInsert(heap1, st3);
	heapNodeChange(heap1, st3, 5);
	fprintf(stdout, "%i\n", heapNodeRemove(heap1)->lengthSum);
	fprintf(stdout, "%i\n", heapNodeRemove(heap1)->lengthSum);
	fprintf(stdout, "%i\n", heapNodeRemove(heap1)->lengthSum);
	fprintf(stdout, "%i\n", heapNodeRemove(heap1)->lengthSum);
	/*if(heapNodeRemove(heap1)->lengthSum!=3) return 0;
	if(heapNodeRemove(heap1)->lengthSum!=5) return 0;
	if(heapNodeRemove(heap1)->lengthSum!=5) return 0;*/
	if(heap1==NULL) return 0;
	if((*heap1)!=NULL) return 0;
	return 1;
}

int main() {
	if(!test1()) fprintf(stdout, "test1\n");
	if(!test2()) fprintf(stdout, "test2\n");
	if(!test3()) fprintf(stdout, "test3\n");
	if(!test4()) fprintf(stdout, "test4\n");
	if(!test5()) fprintf(stdout, "test5\n");

	return 1;
}

