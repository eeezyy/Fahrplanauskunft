#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
// visited constants
#define NOTVISITED 0
#define VISITED_BEGINN 1
#define VISITED_END 2
#define BUFFERSIZE 2024
#define CHANGETIME 5

char *programname;

// parse inputfile
// make station objects and put it in list
// return number of stations
int load(char *readIn, list **listRoot);
// remove repeating blanks and tabs
char *trimTabsAndBlanks(char *string);
// initiate station object
// check if station already exists
station* initHalt(char *halt, list **listRoot);
// initiate path object
path* initPath(char *mark, int length);
// insert station into adjazenz list
int adjazenzInsert(list **listRoot, station *stationFrom, station *stationDestination, int length, char *mark);
// remove station duplicates
int listClean(list **listRoot);
// remove new line
void chomp(char *str);
// search station object with station name
station *searchHalt(char* halt, list **listRoot);


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
	// station names
	char *halt1;
	char *halt2 = NULL;
	char buffer[BUFFERSIZE];
	// counter for stations
	int counter = 0;
	// remember last node in list
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
			// station objects
			// station 0, to remember previous station
			station *station0 = NULL;
			int prevLength = -1;
			station *station1 = NULL;
			int length = -1;
			station *station2 = NULL;

			// unimportant characters
			strtok(NULL, "\"");
			// parse 1. station
			token = trimTabsAndBlanks(strtok(NULL, "\""));
			if (token != NULL) {
				// get first station
				halt1 = token;
				// save station in list
				if(lastListNode!=NULL) {
					lastListNode->next = (list *)malloc(sizeof(list));
					lastListNode = lastListNode->next;
				} else {
					*listRoot = (list *)malloc(sizeof(list));
					lastListNode = *listRoot;
				}
				// set first station as path and insert into list
				lastListNode->p = initPath(mark, 0);
				station1 = initHalt(halt1, listRoot);
				lastListNode->p->halt = station1;
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
				prevLength = length;
				length = (int)strtol(token, NULL, 10);
				// parse following station
				token = trimTabsAndBlanks(strtok(NULL, "\""));
				if(token != NULL) {
					halt2 = token;
					counter++;
				} else {
					// after path length no station name
					fprintf(stderr, "wrong syntax\n");
					exit(EXIT_FAILURE);
					//break;
				}
				// save station in list
				lastListNode->next = (list *)malloc(sizeof(list));
				lastListNode = lastListNode->next;
				lastListNode->p = initPath(mark, 0);
				station2 = initHalt(halt2, listRoot);
				lastListNode->p->halt = station2;

				// put into adjazenzlist
				if(station0!=NULL && prevLength != -1)
					adjazenzInsert(listRoot, station1, station0, prevLength, mark);
				adjazenzInsert(listRoot, station1, station2, length, mark);

				// switch stations, for later use
				halt1 = halt2;
				station0 = station1;
				station1 = station2;
			} while (token != NULL);
			// if station has previous station, add to adjazenzlist
			if (station0 != NULL && station1 != NULL && prevLength != -1) {
				adjazenzInsert(listRoot, station1, station0, prevLength, mark);
			}
		}
	}
	// remove duplicate stations
	listClean(listRoot);
	return counter;
}

int adjazenzInsert(list **listRoot, station *stationFrom, station *stationDestination, int length, char *mark) {
	list *temp = *listRoot;
	while(temp != NULL) {
		// compare station name, to find the station to add direct destination
		if(strcmp(temp->p->halt->name,stationFrom->name) == 0) {
			path *pathNode = NULL;
			// if station has already elements, remember 'next'
			if(temp->p->next != NULL) {
				pathNode = temp->p->next;
			}
			// insert station as path directly after first path node
			temp->p->next = initPath(mark, length);
			temp->p->next->halt = stationDestination;
			temp->p->next->next = pathNode;
			// insert is done successful
			return 1;
		}
		// search ahead with next node
		temp = temp->next;
	}
	// station not found
	return 0;
}

int listClean(list **listRoot) {
	int counter = 0;
	list *temp = *listRoot;
	// remember previous node,
	// to connect if one node was removed
	list *prev = NULL;
	// go through all nodes
	while(temp != NULL) {
		// look for stations in adjazenz list with no next (no destination)
		if(temp->p->next == NULL) {
			if(prev != NULL) {
				// connect previous with next
				prev->next = temp->next;
			} else {
				// if first node in list
				*listRoot = temp;
				if(temp->next == NULL) {
					break;
				} else {
					prev = temp->next;
				}
			}
			// remove and free duplicate node
			free(temp->p);
			free(temp);
			temp = prev;
		} else {
			// set pointer in station to this node in adjazenz list
			temp->p->halt->p = temp->p;
		}
		// remember previous
		prev = temp;
		// go to next node
		temp = temp->next;
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

station* initHalt(char *name, list **listRoot) {
	list *temp = NULL;
	if(listRoot != NULL)
		temp = *listRoot;
	// check if station is already there
	station *existingStation = searchHalt(name, listRoot);
	if(existingStation != NULL)
		return existingStation;

	// if not found, allocate new station, and initialize
	station* stInit;
	stInit = (station*)malloc(sizeof(station));
	stInit->name = name;
	stInit->p = NULL;
	stInit->prev = NULL;
	stInit->lengthSum = -1;
	stInit->visited = NOTVISITED;
	
	return stInit;
}

path* initPath(char *mark, int length)
{
	// allocate new path object and initialize
	path *p = (path*) malloc(sizeof(path));
	p->length = length;
	p->mark = mark;
	p->halt = NULL;
	p->next = NULL;
	return p;	
}

void chomp(char *str)
{
	size_t p=strlen(str);
	// remove new line
	if(str[p-1] == '\n')
	{
		str[p-1]='\0';
	}
}

station *searchHalt(char* halt, list **listRoot)
{
	list *elem = *listRoot;
	// check if station is there
	while(elem != NULL)
	{
		if(elem->p->halt != NULL) 
		{
			if((strcmp(elem->p->halt->name,halt) == 0))
			{
				// return existing station object
				return elem->p->halt;
			}
		}
		elem = elem->next;
	}
	return NULL;
}

