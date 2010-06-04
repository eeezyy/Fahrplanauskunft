#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "heap.h"
#define NOTVISITED 0
#define VISITED_BEGINN 1
#define VISITED_END 2
#define SIZE 2003
#define BUFFERSIZE 501

char *programname;

// EINLESE-STRUCT
typedef struct node
{
	char name[50];
	int id;
	int prev;
	int lengthSum;
	int visited;
} station;

typedef struct edge
{
	station *halt;
	int length;
	char mark[10];
	struct edge *next;
} path;

typedef struct treenode
{
	station *halt;
	struct treenode *prev;
	struct treenode *next;
} heapnode;

void load(char *readIn);
char *trimTabsAndBlanks(char *string);

// USAGE-NACHRICHT
void printF1()
{
	fprintf(stderr, "USAGE: %s FILENAME\n", programname);
}

void load(char *readIn) {
	FILE *input;
	//char *read;
	char *token;
	char buffer[BUFFERSIZE];

	input = fopen(readIn, "r");
	if(!input) {
		fprintf(stderr,"File doesn't exist.\n");
		exit(EXIT_FAILURE);
	}

	while(fgets(buffer, BUFFERSIZE, input) != NULL) {
		token = trimTabsAndBlanks(strtok(buffer, ":\n"));
		if (token != NULL) {
			fprintf(stdout, "Station: %s\n", token);
			// unimportant characters
			strtok(NULL, "\"");
			// Parse 1. station
			token = trimTabsAndBlanks(strtok(NULL, "\""));
			if (token != NULL) {
				fprintf(stdout, token);
			} else {
				continue	;
			}
			do {
				// Parse lenght, \n for after the last station
				token = trimTabsAndBlanks(strtok(NULL, "\"\n"));
				if(token == NULL) {
					break;
				}
				int length = (int)strtol(token, NULL, 10);
				fprintf(stdout, "length '%s', %i\n", token, length);
				// Parse station
				token = trimTabsAndBlanks(strtok(NULL, "\""));
				fprintf(stdout, token);
			} while (token != NULL);
			fprintf(stdout, "\n");
		}
	}
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
					// saving the time as "timeBetween"
							timeBetween = 0;
							zahl++;
					// saving second station as "st2"				
						if(zahl == 1)
						{
							strcpy(st2,token);
							fprintf(stdout,"LINIE: %s\t1.Station: %s\tDauer:%d\t2.Station %s\n", linie, st1,timeBetween,st2);
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
								
								fprintf(stdout,"\nNEWLINIE: %s\t1.Station: %s\tDauer:%d\t2.Station %s\n", linie, st1,timeBetween,st2);
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
					
						if((read == NULL))
						{
							while(read == NULL)
							{
								read = fgets(buffer, 501,input);
								if(read != NULL)
								{
									break;
								}
							}
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


void chomp(char *str) {
   size_t p=strlen(str);
   /* '\n' mit '\0' überschreiben */
   if(str[p-1] == '\n')
   {
	str[p-1]='\0';
   }
}
