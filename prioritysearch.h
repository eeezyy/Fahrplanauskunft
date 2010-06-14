
void search(station *startStation, station *endStation, heapnode **heap) {
	station *currentStation = startStation;
	path *tempPath = currentStation->p;
	station *tempStation = startStation;
	while(currentStation != endStation) {
		station *test = NULL;
		if(tempPath != NULL)
			test = tempPath->halt;
		while(tempPath != NULL) {
			if (currentStation->lengthSum != -1) {
				tempPath->halt->lengthSum = currentStation->lengthSum + tempPath->length;
			} else {
				tempPath->halt->lengthSum = tempPath->length;
			}
			if(tempPath->halt != test && tempPath->halt->visited == NOTVISITED) {
				tempPath->halt->prev = test;
				fprintf(stdout, "%s -> %s\n", test->name, tempPath->halt->name);
				heapNodeInsert(heap, tempPath->halt);
			}
			tempPath = tempPath->next;
		}

		//tempStation = currentStation;

		if(currentStation->visited != VISITED_BEGINN) {
			tempPath = currentStation->p;
			if(tempPath != NULL && tempPath->halt != NULL)
				tempPath->halt->visited = VISITED_BEGINN;
		}
		//fprintf(stdout, "%s length: %i\n", currentStation->name, currentStation->lengthSum);
		if(currentStation == endStation) {
			return;
		}
		if(*heap != NULL) {
			currentStation = heapNodeRemove(heap);
		}
		//if(currentStation != tempStation)
		//	currentStation->prev = tempStation;
	}
}

void printStations(station *endStation){
	if(endStation != NULL) {
		if(endStation->prev != NULL) {
			printStations(endStation->prev);
		}
		fprintf(stdout, "%s\n", endStation->name);
	}
}
