#include "types.h"
#include "fahrplanauskunft.h"
#include "heap.h"

//hash-table in working progress


int main(int argc, char *argv[]) 
{
	char* readIn = NULL;
	path stationlist[SIZE];
	path* haltlist = stationlist;	//Pointer to Array-List(stationlist)
	int i;
	
	// One parameter for input filename
	programname = argv[0];
	if(argc != 2)
	{
		printF1();
		return EXIT_FAILURE;
	}
	readIn = argv[1];
	//load(readIn);
	//test = (int) makeHash(SIZE, readIn);
	//fprintf(stdout, "Ergebnis von der Hash-Funktion: %d\n", test);

	/*for(i = 0; i < SIZE; i++)
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
		
	}	*/
	heapnode **heap;
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

	heapNodeInsert(heap, &st1);
	heapNodeInsert(heap, &st2);
	heapNodeInsert(heap, &st3);
	heapNodeInsert(heap, &st4);
	heapNodeInsert(heap, &st5);

	station *out = NULL;

	//out = heapNodeRemove(heap);
	do {
		out = heapNodeRemove(heap);
		fprintf(stdout, "%s(%i)\n", out->name, out->lengthSum);
	} while(out != NULL);
	return EXIT_SUCCESS;
}

