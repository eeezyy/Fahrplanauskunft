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
	return EXIT_SUCCESS;
}
