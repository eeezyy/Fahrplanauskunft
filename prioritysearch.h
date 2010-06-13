
void search(station *startStation, station *endStation, heapnode **heap) {
	station *currentStation = startStation;
	path *tempPath = currentStation->p;
	station *tempStation = startStation;
	while(currentStation != endStation) {
		while(tempPath != NULL) {
			if(tempPath->halt->lengthSum > 0) {
				fprintf(stdout, "lengthSum > 0\n");
			}
				fprintf(stdout, "test1\n");
			if (currentStation->lengthSum != -1)
				tempPath->halt->lengthSum = currentStation->lengthSum + tempPath->length;
			else
				tempPath->halt->lengthSum = tempPath->length;
			heapNodeInsert(heap, tempPath->halt);
			if(tempPath->halt == endStation) {
				fprintf(stdout, "endStation 2.\n");
			}
			tempPath->halt->visited = VISITED_BEGINN;
			tempPath = tempPath->next;
		}
				fprintf(stdout, "test2\n");
		currentStation = heapNodeRemove(heap);
		currentStation->prev = startStation;
		if(currentStation->visited != VISITED_BEGINN)
			tempPath = currentStation->p;
		fprintf(stdout, "%s length: %i\n", currentStation->name, currentStation->lengthSum);
		if(currentStation == endStation) {
			fprintf(stdout, "endStation 2.\n");
			return;
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
