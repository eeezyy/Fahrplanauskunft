
void search(station *startStation, station *endStation, heapnode **heap) {
	station *currentStation = startStation;
	path *tempPath = currentStation->p;
	station *tempStation = startStation;
	while(currentStation != endStation) {
		while(tempPath != NULL) {
			if (currentStation->lengthSum != -1) {
				tempPath->halt->lengthSum = currentStation->lengthSum + tempPath->length;
			} else {
				tempPath->halt->lengthSum = tempPath->length;
			}
			heapNodeInsert(heap, tempPath->halt);
			tempPath = tempPath->next;
		}
		if(currentStation != tempStation)
			currentStation->prev = tempStation;

		tempStation = currentStation;

		if(currentStation->visited != VISITED_BEGINN) {
			tempPath = currentStation->p;
			if(tempPath != NULL && tempPath->halt != NULL)
				tempPath->halt->visited = VISITED_BEGINN;
		}
		fprintf(stdout, "%s length: %i\n", currentStation->name, currentStation->lengthSum);
		if(currentStation == endStation) {
			fprintf(stdout, "endStation 2.\n");
			return;
		}
		if(*heap != NULL) {
			currentStation = heapNodeRemove(heap);
		}
	}
}

void printStations(station *endStation){
	if(endStation != NULL) {
		if(endStation->prev != NULL) {
			printStations(endStation);
		}
	}
	fprintf(stdout, "%s\n", endStation->name);
}
