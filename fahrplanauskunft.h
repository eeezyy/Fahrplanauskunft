#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#define NOTVISITED 0
#define VISITED_BEGINN 1
#define VISITED_END 2
#define BUFFERSIZE 501
long SIZE = 0;

char *programname;
int load(char *readIn, path* inputp);
char *trimTabsAndBlanks(char *string);
long makeHash(long size, char* term);
station* initHalt(station* halt);
void printHalt(station *halt);
path* inputpath(char mark[10] , int length, char* st1, path* inputp);
void displaypath(path *inputp);


//void setValue(path* haltlist, char* st1, int time, char* st2);

// USAGE-NACHRICHT
void printF1()
{
	fprintf(stderr, "USAGE: %s FILENAME\n", programname);
}

int load(char *readIn, path* inputp) {
	FILE *input;
	char *token;
	char *mark;
	char *halt1;
	char *halt2 = NULL;
	int length,hash1,hash2;
	char buffer[BUFFERSIZE];
	int counter = 0;

	input = fopen(readIn, "r");
	if(!input) {
		fprintf(stderr,"File doesn't exist.\n");
		exit(EXIT_FAILURE);
	}

	while(fgets(buffer, BUFFERSIZE, input) != NULL) {
		token = trimTabsAndBlanks(strtok(buffer, ":\n"));
		if (token != NULL) {
			mark = token;
			//fprintf(stdout, "Station: %s\n", token);

			// unimportant characters
			strtok(NULL, "\"");
			// Parse 1. station
			token = trimTabsAndBlanks(strtok(NULL, "\""));
			if (token != NULL) {
				// create here halt1 struct
				halt1 = token;
			inputp = inputpath(mark,length,halt1,inputp);
				counter++;
				//fprintf(stdout, token);
			} else {
				// parse next line
				continue	;
			}
			do {
				// Parse lenght, \n for after the last station
				// there is no need to trim tabs and blanks
				token = strtok(NULL, "\"\n");
				if(token == NULL) {
					break;
				}
				length = (int)strtol(token, NULL, 10);
				
				//inputpath(mark,length,halt1,inputp);
				//fprintf(stdout, "length '%s', %i\n", token, length);
				// Parse station
				token = trimTabsAndBlanks(strtok(NULL, "\""));
				if(token != NULL) {
					halt2 = token;
					//inputp = inputpath(mark,length,halt1,inputp);
//<! ---inputp = inputpath(mark,length,halt2,inputp);
					counter++;
					//fprintf(stdout, token);
				}
				//hash1 = (int) makeHash(SIZE, halt1);
				//hash2 = (int) makeHash(SIZE, halt2);
				// Create here path struct and halt2 struct
				//fprintf(stdout, "Mark: '%s', halt1: '%s' hash: %d, halt2: '%s' hash: %d, length: '%i'\n", mark, halt1, hash1, halt2,hash2, length);
				halt1 = halt2;
		inputp = inputpath(mark,length,halt1,inputp);
			} while (token != NULL);
		}
	}
	//fprintf(stdout,"Anzahl der stationen %d\n", counter);
	return counter;
}

char *trimTabsAndBlanks(char *string) {
	// use more efficient 
	char *buffer;
	int i;
	int wasBlank = 0;
	int wasTab = 0;
	int newIterator = 0;
	if(string != NULL) {
		buffer = malloc(BUFFERSIZE * sizeof(char));
		for(i = 0, newIterator = 0; i < strlen(string); i++, newIterator++) {
			if(string[i]!=' ' && string[i]!='\t') {
				buffer[newIterator] = string[i];
				wasBlank = 0;
				wasTab = 0;
			} else if(string[i]==' ') {
				// to remove first blank
				//if(wasBlank==0 && i!=0) {
				if(wasBlank==0) {
					buffer[newIterator] = string[i];
					wasBlank = 1;
				} else {
					newIterator--;
				}
			} else if(string[i]=='\t') {
				// to remove first tab
				//if(wasTab==0 && i!=0) {				
				if(wasTab==0) {
					buffer[newIterator] = string[i];
					wasTab = 1;
				} else {
					newIterator--;
				}
			}
		}
	} else {
		return string;
	}
	return buffer;
}

long makeHash(long size, char *term)
{
	int i=0;
	long hash = 0;
	int termlength = 0;
	long double factor;


	if (strlen(term)==0)
		return -1;
		
	termlength=strlen(term);	//bezeichnet die Stringlänge n
		
	factor=31;			
	factor= pow(factor,termlength); //wird für die for-Schleife verwendet

	for (i=0; i < termlength; i++)
	{
		factor = (factor/31);
		hash=(int)(hash + term[i]*factor)%size;
	}
	return hash;
}

station* initHalt(station* halt)
{
	station* stInit;
	stInit = (station*)malloc(sizeof(station));
		strcpy(stInit->name, "NULL");
		stInit->id = 0;
		stInit->prev = 0;
		stInit->lengthSum = 0;
		stInit->visited = -1;
		
		return stInit;
}

void printHalt(station* halt)
{
		fprintf(stdout,"stationname: %s\tID: %d\tPREV: %d\tSumme: %d\tvisited: %d ", halt->name, halt->id, halt->prev, halt->lengthSum, halt->visited);
}


path* inputpath(char mark[10] , int length, char* st1, path* inputp)
{
	station* stat = (station*)malloc(sizeof(station));
	strcpy(stat->name, st1);
	path *p = (path*) malloc(sizeof(path));
	p->length = length;
	strcpy(p->mark, mark);
	p->halt = stat;
	
	if(inputp == NULL)
	{
		
		inputp = p;
	}
	else
	{
		inputp->next = p;
	}
		return p;	
}

void displaypath(path *inputp)
{
		int counter = 0;
		fprintf(stdout,"read-process launched\n");
		while(inputp->next != NULL)
		{
				fprintf(stdout,"length: %d\tmark: %s\tname: %s\n", inputp->length, inputp->mark, inputp->halt->name);
				inputp = inputp->next;
				counter++;
		}
		fprintf(stdout,"\nInsgesamt sind es %d Stationen\n", counter);
}

