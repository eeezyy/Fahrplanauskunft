// priority search first - algorithm
void search(station *startStation, station *endStation, heapnode **heap);
// print stations recursive, beginning with endStation, and using prev attribute
station *printStations(station *endStation);

void search(station *startStation, station *endStation, heapnode **heap) {
	// set start station as visited
	startStation->visited = VISITED_BEGINN;
	station *currentStation = startStation;
	// currently visiting station, path is to used as adjazenz node
	path *tempPath = currentStation->p;
	path *previousPath = NULL;
	while(currentStation != endStation) {
		// remember path, (first node in adjazenz list)
		path *firstNodePath = NULL;
		if(tempPath != NULL) {
			firstNodePath = tempPath;
		}
		// to go through all destination from current station
		while(tempPath != NULL) {
			// when this station is not first station of adjazenz list, and not visited yet
			if(tempPath->halt != firstNodePath->halt && tempPath->halt->visited == NOTVISITED) {
				// set distance to start station in (new) station
				int newLength;
				if (firstNodePath->halt->lengthSum != -1) {
					 newLength = firstNodePath->halt->lengthSum + tempPath->length;
				} else {
					newLength = tempPath->length;
				}
				// count in change
				path *markPath = NULL;
				if(firstNodePath->halt != NULL && firstNodePath->halt->prev != NULL)
					markPath = firstNodePath->halt->prev->p;
				while(markPath != NULL) {
					if(markPath->halt == firstNodePath->halt) {
							if(strcmp(markPath->mark, tempPath->mark) != 0) {
								newLength += CHANGETIME;
							}
					}
					markPath = markPath->next;
				}
				
				if(tempPath->halt->lengthSum == -1 || tempPath->halt->lengthSum > newLength) {
					tempPath->halt->lengthSum = newLength;
					
					// set previous station to this station
					tempPath->halt->prev = firstNodePath->halt;

					// check if node is already in heap, then remove it
					if(heap != NULL && (*heap) != NULL && (*heap)->halt == tempPath->halt)
						heapNodeRemove(heap);
					else if(heap != NULL && (*heap) != NULL)
						checkHeapSort((*heap)->left, (*heap)->right, tempPath->halt);
					// insert station to the heap
					heapNodeInsert(heap, tempPath->halt);
				}
			}
			tempPath = tempPath->next;
		}
		// if not yet visited, go to station
		if(currentStation->visited != VISITED_BEGINN) {
			// visit station
			previousPath = tempPath;
			tempPath = currentStation->p;
			if(tempPath != NULL && tempPath->halt != NULL)
				// set as visited
				tempPath->halt->visited = VISITED_BEGINN;
		}
		// if station is reached, exit function
		if(currentStation == endStation) {
			return;
		}
		// if heap has element
		if(*heap != NULL) {
			// get station with smallest distance
			currentStation = heapNodeRemove(heap);
		}
	}
}

station *printStations(station *endStation){
	// remember following station, to look up which path to go
	station *next = NULL;
	if(endStation != NULL) {
		if(endStation->prev != NULL) {
			// this will be called as long as the end of the list ist reached
			// the end is the start station, which we will print first
			next = printStations(endStation->prev);
		}
		// look up path in adjazenz list
		path *tempPath = endStation->p;
		if(next != NULL) {
			while(tempPath != NULL) {
				if(tempPath->halt == next) {
					// if found, get mark of the path
					fprintf(stdout, "-> %s\n", tempPath->mark);
					break;
				}
				tempPath = tempPath->next;
			}
		}
		fprintf(stdout, "%s\n", endStation->name);
	}
	return endStation;
}
