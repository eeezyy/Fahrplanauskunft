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

	displaypath(listRoot);

	if(count == 0) {
		fprintf(stdout, "Datei enthält keine Stationen\n");
		exit(EXIT_SUCCESS);
	}
	//buffer for defining source and destination halt
	char source[BUFFERSIZE];
	char destination[BUFFERSIZE];
	
	fprintf(stdout, "Start: ");
	fgets(source, BUFFERSIZE, stdin);
	chomp(source);
	fprintf(stdout, "Ziel: ");
	fgets(destination, BUFFERSIZE, stdin);
	chomp(destination);
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
			fprintf(stderr, "Mindestens eine Station ist nicht verfügbar!\n");
			exit(EXIT_SUCCESS);
		}
	}
	search(startStation, endStation, heapBeginn);
	fprintf(stdout, "\nRoute\n-------------------\n");
	printStations(endStation);
	fprintf(stdout, "Fahrtdauer: %i\n", endStation->lengthSum);
	//printTestCases(listRoot, readIn);
				
	return EXIT_SUCCESS;
}

