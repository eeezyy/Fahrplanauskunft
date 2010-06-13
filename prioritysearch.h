
void search(station *startStation, station *endStation, heapnode **heap) {
	station *currentStation = NULL;
	while(currentStation == endStation) {
		path *tempPath = startStation->p;
		station *tempStation = startStation;
		while(tempPath != NULL) {
			if(tempPath->halt->lengthSum > 0) {
				fprintf(stdout, "lengthSum > 0\n");
			}
			tempPath->halt->lengthSum = startStation->lengthSum + tempPath->length;
			heapNodeInsert(heap, tempPath->halt);
			tempPath = tempPath->next;
			if(tempPath->halt == endStation) {
				fprintf(stdout, "endStation 2.\n");
			}
		}
		currentStation = heapNodeRemove(heap);
		currentStation->prev = startStation;
		if(tempPath->halt == endStation) {
			fprintf(stdout, "endStation 2.\n");
			return;
		}
	}
}

