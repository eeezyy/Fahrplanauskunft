#include "types.h"
#include "fahrplanauskunft.h"
#include "heap.h"
#include "prioritysearch.h"


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
	station *startStation, *endStation;

	//displaypath(listRoot);


	//buffer for defining source and destination halt
	char source[40];
	char destination[40];
	
	fprintf(stdout, "\nBitte die Station, welche als Anfangspunkt für die Route gilt, eingeben:\n");
	fgets(source, 25,stdin);
	chomp(source);
	fprintf(stdout, "\nBitte Zielstation eingeben:\n");
	fgets(destination, 25,stdin);
	chomp(destination);
	//fprintf(stdout, "\n%s\t %s\n", source, destination);
	if(strcmp(source, destination) == 0)
	{
		fprintf(stdout, "Sie befinden sich bereits an der eingegebenen Station.\n");
		exit(EXIT_SUCCESS);
	}
	else
	{
		startStation = searchHalt(source, listRoot);
		endStation = searchHalt(destination, listRoot);
		if(startStation == NULL || endStation == NULL) {
			fprintf(stdout, "Mindestens eine Station ist nicht verfügbar!\n");
			exit(EXIT_SUCCESS);
		}
	}
	
				
	return EXIT_SUCCESS;
}

