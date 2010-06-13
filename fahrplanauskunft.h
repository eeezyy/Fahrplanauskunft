#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#define NOTVISITED 0
#define VISITED_BEGINN 1
#define VISITED_END 2
#define BUFFERSIZE 501

char *programname;

int load(char *readIn, list **listRoot);
char *trimTabsAndBlanks(char *string);
station* initHalt(char *halt, list **listRoot);
path* initPath(char mark[10] , int length);
void displaypath(list **listRoot);
int adjazenzInsert(list **listRoot, station *stationFrom, station *stationDestination, int length, char *mark);
int listClean(list **listRoot);


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

			station *station0 = NULL;
			station *station1;
			station *station2;

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
				length = (int)strtol(token, NULL, 10);
				
				// parse following station
				token = trimTabsAndBlanks(strtok(NULL, "\""));
				if(token != NULL) {
					halt2 = token;
					counter++;
				} else break;

				// save station in temporary list, to move later to hashtable
				lastListNode->next = (list *)malloc(sizeof(list));
				lastListNode = lastListNode->next;
				lastListNode->p = initPath(mark, 0);
				station2 = initHalt(halt2, listRoot);
				lastListNode->p->halt = station2;

				// put into adjazenzlist
				if(station0!=NULL)
					adjazenzInsert(listRoot, station1, station0, length, mark);
				adjazenzInsert(listRoot, station1, station2, length, mark);

				halt1 = halt2;
				station0 = station1;
				station1 = station2;
			} while (token != NULL);
			if (station0 != NULL && station1 != NULL) {
				adjazenzInsert(listRoot, station1, station0, length, mark);
			}
		}
	}
	listClean(listRoot);
	return counter;
}

int adjazenzInsert(list **listRoot, station *stationFrom, station *stationDestination, int length, char *mark) {
	list *temp = *listRoot;
	while(temp != NULL) {
		if(strcmp(temp->p->halt->name,stationFrom->name) == 0) {
			path *pathNode = NULL;
			if(temp->p->next != NULL) {
				pathNode = temp->p->next;
			}
			temp->p->next = initPath(mark, length);
			temp->p->next->halt = stationDestination;
			temp->p->next->next = pathNode;
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}

int listClean(list **listRoot) {
	int counter = 0;
	list *temp = *listRoot;
	list *prev = NULL;
	while(temp != NULL) {
		if(temp->p->next == NULL) {
			prev->next = temp->next;
			free(temp->p);
			free(temp);
			temp = prev;
		} else {
			temp->p->halt->p = temp->p;
		}
		prev = temp;
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
	list *temp = *listRoot;
	while(temp != NULL) {
		if(temp->p->halt != NULL) {
			if(strcmp(temp->p->halt->name,name) == 0) {
				return temp->p->halt;
			}
		}
		temp = temp->next;
	}
	station* stInit;
	stInit = (station*)malloc(sizeof(station));
	strcpy(stInit->name, name);
	stInit->p = NULL;
	stInit->prev = NULL;
	stInit->lengthSum = -1;
	stInit->visited = NOTVISITED;
	
	return stInit;
}

path* initPath(char *mark, int length)
{
	path *p = (path*) malloc(sizeof(path));
	p->length = length;
	strcpy(p->mark, mark);
	p->halt = NULL;
	p->next = NULL;
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
		path *temp = listNode->p->next;
		while(temp != NULL) {
			fprintf(stdout,"\tlength: %d\tmark: %s\tname: %s\n", temp->length, temp->mark, temp->halt->name);
			temp = temp->next;
		}
		listNode = listNode->next;
	}
	fprintf(stdout,"\nInsgesamt sind es %d Stationen\n", counter);
}

