
void search(station *startStation, station *endStation, heapnode **heap) {
	startStation->visited = VISITED_BEGINN;
	station *currentStation = startStation;
	path *tempPath = currentStation->p;
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
				heapNodeInsert(heap, tempPath->halt);
			}
			tempPath = tempPath->next;
		}

		if(currentStation->visited != VISITED_BEGINN) {
			tempPath = currentStation->p;
			if(tempPath != NULL && tempPath->halt != NULL)
				tempPath->halt->visited = VISITED_BEGINN;
		}
		if(currentStation == endStation) {
			return;
		}
		if(*heap != NULL) {
			currentStation = heapNodeRemove(heap);
		}
	}
}

station *printStations(station *endStation){
	station *next = NULL;
	if(endStation != NULL) {
		if(endStation->prev != NULL) {
			next = printStations(endStation->prev);
		}
		path *tempPath = endStation->p;
		if(next != NULL) {
			while(tempPath != NULL) {
				if(tempPath->halt == next) {
					fprintf(stdout, "mark: %s\n", tempPath->mark);
					break;
				}
				tempPath = tempPath->next;
			}
		}
		fprintf(stdout, "%s\n", endStation->name);
	}
	return endStation;
}
