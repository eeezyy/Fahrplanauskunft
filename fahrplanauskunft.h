#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define NOTVISITED 0
#define VISITED_BEGINN 1
#define VISITED_END 2
#define SIZE 2003

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

void heapInsert(station insert);
station heapGetMin();

// USAGE-NACHRICHT
void printF1()
{
	fprintf(stderr, "USAGE: ./fahrplanauskunft FILE\n");
}

void load(char* readIn)
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
		read = fgets(buffer,501,input);
		if(read == NULL)
		{
			while (fgets (buffer, 501, input)!=NULL)
			{
				read = fgets(buffer, 501,input);
				if(read != NULL)
				{
					break;
				}
			}
		}
		
		while(read != NULL)
		{
			zahl = 0;
			turn = 0;
			token = strtok(read,":");
			strcpy(linie,token);
				//fprintf(stdout, "LINIE: %s\n",linie);
				while(strcmp(token,"\n") != 0)
				{
					token = strtok(NULL,"\"");
					
						if(strcmp(token," ") == 0)
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
						token = strtok(NULL,"\"");
						
							if(strcmp(token," ") == 0)
							{
								token = strtok(NULL,"\"");
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
					
					}
				}	
			}
			read = fgets(buffer, 501,input);
		}
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
