#include "types.h"
#include "fahrplanauskunft.h"
#include "debug.h"
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
		fprintf(stderr, "Sie befinden sich bereits an der eingegebenen Station.\n");
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
	search(startStation, endStation, heapBeginn);
	fprintf(stdout, "\nVerbindung\n-----------\n");
	printStations(endStation);
	fprintf(stdout, "Fahrtdauer: %i\n", endStation->lengthSum);
				
	return EXIT_SUCCESS;
}

