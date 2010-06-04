#include "fahrplanauskunft.h"
//hash-table in working progress


int main(int argc, char *argv[]) 
{
	char* readIn = NULL;
	// TO-DO change parameter, using getop, 
	// for use in terminal and webinterface
	programname = argv[0];
	if(argc != 2)
	{
		printF1();
		return EXIT_FAILURE;
	}
	readIn = argv[1];
	load(readIn);
	return EXIT_SUCCESS;
}
