struct edge;

typedef struct node {
	char *name;
	// pointer to the adjazenz pathnode
	struct edge *p;
	struct node *prev;
	// distance from startStation
	int lengthSum;
	int visited;
} station;

typedef struct edge {
	station *halt;
	// distance from previous station
	int length;
	char *mark;
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

typedef struct liste {
	path *p;
	struct liste *next;
} list;
