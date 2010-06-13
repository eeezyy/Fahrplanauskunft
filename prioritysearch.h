
void search(station *startStation, station *endStation, heapnode **heap) {
	station *currentStation = startStation;
	while(currentStation != endStation) {
		path *tempPath = currentStation->p;
		station *tempStation = startStation;
		while(tempPath != NULL) {
			if(tempPath->halt->lengthSum > 0) {
				fprintf(stdout, "lengthSum > 0\n");
			}
				fprintf(stdout, "test1\n");
			tempPath->halt->lengthSum = startStation->lengthSum + tempPath->length;
			heapNodeInsert(heap, tempPath->halt);
			if(tempPath->halt == endStation) {
				fprintf(stdout, "endStation 2.\n");
			}
			tempPath = tempPath->next;
		}
				fprintf(stdout, "test2\n");
		currentStation = heapNodeRemove(heap);
		currentStation->prev = startStation;
		fprintf(stdout, "%s\n", currentStation->name);
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
