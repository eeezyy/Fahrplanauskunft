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

		// when this station is not first station of adjazenz list, and not visited yet
		if(tempPath->halt != test && tempPath->halt->visited == NOTVISITED) {
				// set distance to start station in (new) station
				fprintf(stdout, "%s -> %s: %i(%i) %s: %i\n", test->name, tempPath->halt->name, tempPath->halt->lengthSum, tempPath->length, test->name, test->lengthSum);
				if (test->lengthSum != -1) {
					tempPath->halt->lengthSum = test->lengthSum + tempPath->length;
				} else {
					tempPath->halt->lengthSum = tempPath->length;
				}
				fprintf(stdout, "%s -> %s: %i(%i) %s: %i\n\n", test->name, tempPath->halt->name, tempPath->halt->lengthSum, tempPath->length, test->name, test->lengthSum);
				// count in change
				path *markPath = NULL;
				if(test != NULL)
					markPath = test->p;
				while(markPath != NULL) {
					if(markPath->halt == test) {
						if(mark != NULL) {
							if(strcmp(markPath->mark, tempPath->mark) != 0) {
								fprintf(stdout, "Umstieg: %s (%s) - %s (%s)\n", markPath->halt->name, markPath->mark, tempPath->halt->name, tempPath->mark);
								tempPath->halt->lengthSum += CHANGETIME;
							}
						}
					}
					markPath = markPath->next;
				}

				// set previous station to this station
				tempPath->halt->prev = test;
				// insert station to the heap
				heapNodeInsert(heap, tempPath->halt);
				if(heap != NULL)
					showHeapContent(*heap, NULL);
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
