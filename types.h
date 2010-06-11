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

typedef struct treenode {
	station *halt;
	// distance = shortest path from node to NULL
	// where left.dist >= right.dist
	int dist;
	struct treenode *left;
	struct treenode *right;
} heapnode;
