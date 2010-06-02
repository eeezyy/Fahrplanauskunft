#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "fahrplanauskunft.h"



int main(int argc, char *argv[]) 
{
	if(argc != 2)
	{
		printF1();
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
