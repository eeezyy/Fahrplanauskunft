
// EINLESE-STRUCT
struct subway
{
	char station[25];
	int time;
	
	subway* nxt;
	//subway* prev;
};

// USAGE-NACHRICHT
void printF1()
{
	fprintf(stderr, "USAGE: ./fahrplanauskunft FILE\n");
}
