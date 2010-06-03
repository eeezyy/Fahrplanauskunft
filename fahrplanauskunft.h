#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

#define NOTVISITED 0
#define VISITED_BEGINN 1
#define VISITED_END 2

void heapInsert(station insert);
station heapGetMin();

// USAGE-NACHRICHT
void printF1()
{
	fprintf(stderr, "USAGE: ./fahrplanauskunft FILE\n");
}
