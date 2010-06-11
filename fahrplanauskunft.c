#include "types.h"
#include "fahrplanauskunft.h"
#include "heap.h"

//hash-table in working progress


int main(int argc, char *argv[]) 
{
	char* readIn = NULL;
	int i, j = 0;
	
	
	// One parameter for input filename
	programname = argv[0];
	if(argc != 2)
	{
		printF1();
		return EXIT_FAILURE;
	}
	
	readIn = argv[1];
	j = load(readIn);
	SIZE = (long)(4 * j + 3);
	fprintf(stdout, "SIZE: %ld", SIZE);
	path stationlist[SIZE];	//vertical - list
	path* haltlist = stationlist;	//Pointer to Array-List(stationlist) <- horizontal
	
	//test = (int) makeHash(SIZE, readIn);
	//fprintf(stdout, "Ergebnis von der Hash-Funktion: %d\n", test);

	for(i = 0; i < SIZE; i++)
	{
		stationlist[i].length = 0;
		strcpy(stationlist[i].mark,"NULL");
		stationlist[i].halt = initHalt(stationlist[i].halt);
		stationlist[i].next = NULL;
	}	
	
	for(i = 0; i < SIZE; i++)
	{
		printHalt(stationlist[i].halt);
		fprintf(stdout,"Länge: %d\tLinie: %s\n",stationlist[i].length, stationlist[i].mark);
		// funktion, das 2te struct ausgegeben wird. 
		
	}	
/*	heapnode **heap = NULL;
	station st1;
	strcpy(st1.name,"Station1");
	st1.lengthSum = 3;

	station st2;
	strcpy(st2.name,"Station2");
	st2.lengthSum = 7;

	station st3;
	strcpy(st3.name,"Station3");
	st3.lengthSum = 15;

	station st4;
	strcpy(st4.name,"Station4");
	st4.lengthSum = 6;

	station st5;
	strcpy(st5.name,"Station5");
	st5.lengthSum = 5;

	heapnode *temp;

	heapNodeInsert(heap, &st1);
	if (heap!=NULL) {
	temp = *heap;
	if(temp != NULL){
		fprintf(stdout, "1. %s\n", temp->halt->name);
		if(temp->left != NULL)
			fprintf(stdout, "1. left %s\n", temp->left->halt->name);
		if(temp->left != NULL)
			fprintf(stdout, "1. right %s\n", temp->right->halt->name);
	}}
	heapNodeInsert(heap, &st2);
	if (heap!=NULL) {
	temp = *heap;
	if(temp != NULL){
		fprintf(stdout, "2. %s\n", temp->halt->name);
		if(temp->left != NULL)
			fprintf(stdout, "2. left %s\n", temp->left->halt->name);
		if(temp->left != NULL)
			fprintf(stdout, "2. right %s\n", temp->right->halt->name);
	}}
	heapNodeInsert(heap, &st3);
	if (heap!=NULL) {
	temp = *heap;
	if(temp != NULL){
		fprintf(stdout, "3. %s\n", temp->halt->name);
		if(temp->left != NULL)
			fprintf(stdout, "3. left %s\n", temp->left->halt->name);
		if(temp->left != NULL)
			fprintf(stdout, "3. right %s\n", temp->right->halt->name);
	}}
	heapNodeInsert(heap, &st4);
	if (heap!=NULL) {
	temp = *heap;
	if(temp != NULL){
		fprintf(stdout, "4. %s\n", temp->halt->name);
		if(temp->left != NULL)
			fprintf(stdout, "4. left %s\n", temp->left->halt->name);
		if(temp->left != NULL)
			fprintf(stdout, "4. right %s\n", temp->right->halt->name);
	}}
	heapNodeInsert(heap, &st5);
	if (heap!=NULL) {
	temp = *heap;
	if(temp != NULL){
		fprintf(stdout, "5. %s\n", temp->halt->name);
		if(temp->left != NULL)
			fprintf(stdout, "5. left %s\n", temp->left->halt->name);
		if(temp->left != NULL)
			fprintf(stdout, "5. right %s\n", temp->right->halt->name);
	}}

	station *out = NULL;
	
	//out = heapNodeRemove(heap);
	do {
		out = heapNodeRemove(heap);
		fprintf(stdout, "%s(%i)\n", out->name, out->lengthSum);
	} while(out != NULL);
*/
	return EXIT_SUCCESS;
}

