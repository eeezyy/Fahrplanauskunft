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
int load(char *readIn, list **listRoot);
char *trimTabsAndBlanks(char *string);
long makeHash(long size, char* term);
station* initHalt(station* halt);
void printHalt(station *halt);
path* initPath(char mark[10] , int length, char* st1);
void displaypath(list **listRoot);


//void setValue(path* haltlist, char* st1, int time, char* st2);

// USAGE-NACHRICHT
void printF1()
{
	fprintf(stderr, "USAGE: %s FILENAME\n", programname);
}

int load(char *readIn, list **listRoot) {
	FILE *input;
	char *token;
	char *mark;
	char *halt1;
	char *halt2 = NULL;
	int length = 0;
	char buffer[BUFFERSIZE];
	int counter = 0;
	list *lastListNode = NULL;

	input = fopen(readIn, "r");
	if(!input) {
		fprintf(stderr,"File doesn't exist.\n");
		exit(EXIT_FAILURE);
	}

	while(fgets(buffer, BUFFERSIZE, input) != NULL) {
		// station mark
		token = trimTabsAndBlanks(strtok(buffer, ":\n"));
		if (token != NULL) {
			mark = token;

			// unimportant characters
			strtok(NULL, "\"");
			// parse 1. station
			token = trimTabsAndBlanks(strtok(NULL, "\""));
			if (token != NULL) {
				// create here halt1 struct
				halt1 = token;
				// save station in temporary list, to move later to hashtable
				if(lastListNode!=NULL) {
					lastListNode->next = (list *)malloc(sizeof(list));
					lastListNode = lastListNode->next;
				} else {
					*listRoot = (list *)malloc(sizeof(list));
					lastListNode = *listRoot;
				}
				lastListNode->p = initPath(mark,length,halt1);
				counter++;
			} else {
				// parse next line
				continue;
			}
			do {
				// parse time to next station
				token = strtok(NULL, "\"\n");
				if(token == NULL) {
					break;
				}
				length = (int)strtol(token, NULL, 10);
				
				// parse following station
				token = trimTabsAndBlanks(strtok(NULL, "\""));
				if(token != NULL) {
					halt2 = token;
					counter++;
				}
				halt1 = halt2;
				// save station in temporary list, to move later to hashtable
				lastListNode->next = (list *)malloc(sizeof(list));
				lastListNode = lastListNode->next;
				lastListNode->p = initPath(mark,length,halt1);
			} while (token != NULL);
		}
	}
	return counter;
}

char *trimTabsAndBlanks(char *string) {
	char *buffer;
	int i;
	int wasBlank = 0;
	int wasTab = 0;
	int newIterator = 0;
	if(string != NULL) {
		// allocate buffer with size of string
		// new string length will be less or equals length of string
		buffer = malloc(BUFFERSIZE * sizeof(*string));
		for(i = 0, newIterator = 0; i < strlen(string); i++, newIterator++) {
			// if not blank or tab, write character to buffer
			if(string[i]!=' ' && string[i]!='\t') {
				buffer[newIterator] = string[i];
				wasBlank = 0;
				wasTab = 0;
			} else if(string[i]==' ') {
				// to remove first blank
				//if(wasBlank==0 && i!=0) {

				// if last character was not blank, write blank to buffer
				// else skip blank
				if(wasBlank==0) {
					buffer[newIterator] = string[i];
					wasBlank = 1;
				} else {
					newIterator--;
				}
			} else if(string[i]=='\t') {
				// to remove first tab
				//if(wasTab==0 && i!=0) {	

				// if last character was not tab, write blank to tab
				// else skip tab			
				if(wasTab==0) {
					buffer[newIterator] = string[i];
					wasTab = 1;
				} else {
					newIterator--;
				}
			}
		}
	} else {
		return NULL;
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


path* initPath(char mark[10] , int length, char* st1)
{
	station* stat = (station*)malloc(sizeof(station));
	strcpy(stat->name, st1);
	path *p = (path*) malloc(sizeof(path));
	p->length = length;
	strcpy(p->mark, mark);
	p->halt = stat;
	return p;	
}

void displaypath(list **listRoot)
{
		list *listNode = *listRoot;
		int counter = 0;
		fprintf(stdout,"read-process launched\n");
		while(listNode != NULL)
		{
			fprintf(stdout,"length: %d\tmark: %s\tname: %s\n", listNode->p->length, listNode->p->mark, listNode->p->halt->name);
			counter++;
			listNode = listNode->next;
		}
		fprintf(stdout,"\nInsgesamt sind es %d Stationen\n", counter);
}

