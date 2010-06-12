#include "types.h"
#include "fahrplanauskunft.h"
#include "heap.h"


int main(int argc, char *argv[]) 
{
	// addresses to heap-root for both threads
	heapnode **heapBeginn = (heapnode **)malloc(sizeof(heapnode *));
	heapnode **heapEnd = (heapnode **)malloc(sizeof(heapnode *));
	char* readIn = NULL;
	int i, j = 0;
	
	
	// One parameter for input filename
	programname = argv[0];
	if(argc != 2)
	{
		printF1();
		return EXIT_FAILURE;
	}
	
	path* inputp = (path *)malloc(sizeof(path));
	//inputp = NULL;
	readIn = argv[1];
	j = load(readIn, inputp);
	SIZE = (long)(4 * j + 3);
	fprintf(stdout, "\n\nSIZE: %ld\n", SIZE);
	path stationlist[SIZE];	//vertical - list
	path* haltlist = stationlist;	//Pointer to Array-List(stationlist) <- horizontal
	
	//test = (int) makeHash(SIZE, readIn);
	//fprintf(stdout, "Ergebnis von der Hash-Funktion: %d\n", test);

/*	for(i = 0; i < SIZE; i++)
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
		
	}*/

	displaypath(inputp);

	return EXIT_SUCCESS;
}

