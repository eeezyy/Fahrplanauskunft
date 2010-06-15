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
	while(currentStation != endStation) {
		// remember station of path, (first node in adjazenz list)
		station *test = NULL;
		// remember mark of station
		char *mark = NULL;
		if(tempPath != NULL) {
			test = tempPath->halt;
			mark = tempPath->mark;
		}
		// to go through all destination from current station
		while(tempPath != NULL) {
			// set distance to start station in (new) station
			if (currentStation->lengthSum != -1) {
				tempPath->halt->lengthSum = currentStation->lengthSum + tempPath->length;
			} else {
				tempPath->halt->lengthSum = tempPath->length;
			}
			fprintf(stdout, "%s -> %s %i\n", test->name, tempPath->halt->name, tempPath->halt->lengthSum);
			// count in change
			if(mark != NULL) {
				if(strcmp(mark, tempPath->mark) != 0) {
					tempPath->halt->lengthSum += CHANGETIME;
				}
			}
			// when this station is not first station of adjazenz list, and not visited yet
			if(tempPath->halt != test && tempPath->halt->visited == NOTVISITED) {
				// set previous station to this station
				tempPath->halt->prev = test;
				// insert station to the heap
				heapNodeInsert(heap, tempPath->halt);
			}
			tempPath = tempPath->next;
		}
		// if not yet visited, go to station
		if(currentStation->visited != VISITED_BEGINN) {
			// visit station
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
