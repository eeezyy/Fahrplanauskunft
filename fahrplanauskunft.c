#include "types.h"
#include "fahrplanauskunft.h"
#include "heap.h"


int main(int argc, char *argv[]) 
{
	// One parameter for input filename
	programname = argv[0];
	if(argc != 2)
	{
		printF1();
		return EXIT_FAILURE;
	}

	// addresses to heap-root for both threads
	heapnode **heapBeginn = (heapnode **)malloc(sizeof(heapnode *));
	//heapnode **heapEnd = (heapnode **)malloc(sizeof(heapnode *));

	list **listRoot = (list **)malloc(sizeof(list *));
	
	char *readIn = argv[1];
	int count = load(readIn, listRoot);

	displaypath(listRoot);

	return EXIT_SUCCESS;
}

