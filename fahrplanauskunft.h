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
void chomp(char *str);
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
//<! ---inputp = inputpath(mark,length,halt1,inputp);
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
//<! ---inputp = inputpath(mark,length,halt1,inputp);
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

void load2(char* readIn)
{
	FILE *input;
	char* read = NULL;
	char* token = NULL;
	char linie[10];
	char st1[30];
	char st2[30];
	int timeBetween;
	char buffer[501];
	int zahl;
	int turn;
	int hash1;
	int hash2;
	
	input = fopen(readIn, "r");
	if(input)
	{
	
		while(feof(input) == 0)
		{
			zahl = 0;
			turn = 0;
			
			do {
				read = fgets(buffer, 501, input);
			} while(read == NULL);
			
			token = strtok(read,":");
			strcpy(linie,token);
				//fprintf(stdout, "LINIE: %s\n",linie);
				while(strcmp(token,"\n") != 0)
				{
					token = strtok(NULL,"\"\t");
					while((strcmp(token," ") == 0) || (strcmp(token,"\t") == 0))
					{
						token = strtok(NULL,"\"");
					}
					//fprintf(stdout, "%s\t",token);
					
					// saving the first  station as "st1"
							strcpy(st1,"NULL");
							hash1 = (int) makeHash(SIZE, st1);
					// saving the time as "timeBetween"
							timeBetween = 0;
							zahl++;
					// saving second station as "st2"				
						if(zahl == 1)
						{
							strcpy(st2,token);
							hash2 = (int) makeHash(SIZE, st2);
							fprintf(stdout,"LINIE: %s\t1.Station: %s\thash: %d\tDauer:%d\t2.Station %s\thash: %d\n", linie, st1, hash1,timeBetween,st2,hash2);
							zahl = 0;
							turn = 1;
						}
				
				while( turn == 1)
				{		
					while(strcmp(token,"\n") != 0)
					{
						token = strtok(NULL,"\"\t");
						
							while((strcmp(token," ") == 0) || (strcmp(token,"\t") == 0))
							{
								token = strtok(NULL,"\"\t");
							}
						strcpy(st1,st2);
						hash1 = (int) makeHash(SIZE, st1);
						//fprintf(stdout, "%s\t",token);
							
							zahl++;
	
						// saving the time as "timeBetween"
							if(zahl == 1)
							{
								timeBetween = (int)strtol(token, NULL, 10);
							}
							
						// saving second station as "st2"				
							if(zahl == 2)
							{
								strcpy(st2,token);
								hash2 = (int) makeHash(SIZE, st2);
								fprintf(stdout,"\nNEWLINIE: %s\t1.Station: %s\thash: %d\tDauer:%d\t2.Station %s\thash: %d\n", linie, st1, hash1,timeBetween,st2,hash2);
								zahl = 0;
							}
							if(strcmp(token,"\n") == 0)
							{
								turn = 0;
								
								strcpy(st1,st2);

								//fprintf(stdout, "%s\t",token);
								// saving the time as "timeBetween"
									if(zahl == 1)
									{
										timeBetween = 0;

									}

								// saving second station as "st2"				
										strcpy(st2,"NULL");
										
										fprintf(stdout,"\nLINIE: %s\t1.Station: %s\tDauer:%d\t2.Station %s\n", linie, st1,timeBetween,st2);
							}
					
				
					
					}
				}	
			}
			read = fgets(buffer, 501,input);
		}
		
		fclose(input);
	}
	else
	{
		fprintf(stderr,"File doesn't exist.\n");
	}
}


void chomp(char *str) 
{
   size_t p=strlen(str);
   /* '\n' mit '\0' überschreiben */
   if(str[p-1] == '\n')
   {
	str[p-1]='\0';
   }
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
	p->next = inputp->next;
	inputp->next = p;
	return p;
}

void displaypath(path *inputp)
{
		int counter = 0;
		fprintf(stdout,"read-process launched\n");
		if(strcmp(inputp->mark, "null"))
		{
			fprintf(stdout,"nullwert!\n\n");
			inputp = inputp->next;
		}
		while(inputp->next != NULL)
		{
				fprintf(stdout,"length: %d\tmark: %s\tname: %s\n", inputp->length, inputp->mark, inputp->halt->name);
				inputp = inputp->next;
				counter++;
		}
		fprintf(stdout,"\nInsgesamt sind es %d Stationen\n", counter);
}
