

// insert new node in heap
heapnode *heapNodeInsert(heapnode **root, station *insert);
// return the smallest node (station with minimal distance)
station *heapNodeRemove(heapnode **heapAddress);
// change the value of one node and rearrange the heap
heapnode **heapNodeChange(heapnode **root, station *change, int newLength);
// core function for heap, merges two heap trees, returns the root node
// normaly used to add a node to heap tree
heapnode *mergeHeaps(heapnode **heapAddress, heapnode *Q);

heapnode *heapNodeInsert(heapnode **root, station *insert) {
	heapnode *newNode = (heapnode *)malloc(sizeof(heapnode));
	// initialize new heapnode
	newNode->halt = insert;
	newNode->dist = 1;
	newNode->left = NULL;
	newNode->right = NULL;

	/*
	if(root == NULL)
		fprintf(stdout, "%s\n", newNode->halt->name);
	else {
		if (*root != NULL) {
			heapnode *temp = *root;
			fprintf(stdout, "ROOT!=NULL, %s, %s\n", temp->halt->name, newNode->halt->name);
		}
		else
			fprintf(stdout, "*ROOT == NULL\n");
	} */

	// add new node to heap
	return mergeHeaps(root, newNode);
}

heapnode *mergeHeaps(heapnode **heapAddress, heapnode *Q) {
	int D;
	// initialize
	heapnode *R = NULL;
	heapnode *T;
	heapnode *P;
	if(heapAddress != NULL)
		P = *heapAddress;
	else
		P = NULL;
	// merge trees
	while(1) {
		if(Q == NULL) {
			//fprintf(stdout, "Q == NULL\n");
			D = (P == NULL)? 1 : P->dist;
			break;
		}
		if(P == NULL) {
			//fprintf(stdout, "P == NULL\n");
			P = Q;
			D = 0;
			break;
		}
		if(P->halt->lengthSum <= Q->halt->lengthSum) {
			T = P->right;
			P->right = R;
			R = P;
			P = T;
		} else {
			T = Q->right;
			Q->right = R;
			R = Q;
			Q = T;
		}
	}

	while(1) {
		// check if done
		if(R == NULL) {
			//fprintf(stdout, "R == NULL\n");
			//fprintf(stdout, "heap-address %i\n", (int)heapAddress);

			// write new root node to the heap address
			*heapAddress = P;
			return P;
		}
		// fix distances
		Q = R->right;
		if(R->left != NULL && R->left->dist < D) {
			D = R->left->dist + 1;
			R->right = R->left;
			R->left = P;
		} else {
			D = D + 1;
			R->right = P;
		}
		R->dist = D;
		P = R;
		R = Q;
	}
}

station *heapNodeRemove(heapnode **heapAddress) {
			//fprintf(stdout, "test merge in remove\n");
	if(heapAddress != NULL) {
		if(*heapAddress != NULL) {
			//fprintf(stdout, "test merge in remove\n");
			heapnode *root = *heapAddress;
			heapnode *temp = root;
			station *halt = root->halt;
			//fprintf(stdout, "before merge in remove\n");
			*heapAddress = mergeHeaps(&(*heapAddress)->left, root->right);
			//fprintf(stdout, "after merge in remove\n");
			free(temp);
			return halt;
		}
	}
	//fprintf(stdout, "HeapNodeRemove NULL\n");
	return NULL;
}

heapnode **recursiveHeapSearch(heapnode **root, heapnode **node, station *findStation, int newLength) {
	heapnode **isFound = NULL;
	if(node == NULL) {
		return NULL;
	}
	if ((*node)->halt->lengthSum < findStation->lengthSum) {
		if((*node)->left != NULL) {
			isFound = recursiveHeapSearch(root, &(*node)->left, findStation, newLength);
		}
		if((*node)->right != NULL && !isFound) {
			isFound = recursiveHeapSearch(root, &(*node)->right, findStation, newLength);
		}
	} else {
		if((*node)->halt == findStation) {
			(*node)->halt->lengthSum = newLength;
			//heapnode *temp = node;
			//node = mergeHeaps(&node->left, node->right);
			//free(temp);
			//return node;
			isFound = node;
			//return node;
		} else {
			return NULL;
		}
	}
	if(*isFound != NULL) {
		fprintf(stdout, "isFOUND != NULL\n");
		if((*node)->left == *isFound){
		fprintf(stdout, "1.\n");
			(*node)->left = NULL;
		}
		else if((*node)->right == *isFound){
		fprintf(stdout, "2.\n");
			(*node)->right = NULL;
		}
		fprintf(stdout, "3.\n");
		//*node = NULL;
		mergeHeaps(root, (*isFound)->left);
		mergeHeaps(root, (*isFound)->right);
		//free(*node);
		heapNodeInsert(root, findStation);
	}
	return NULL;
}

heapnode **heapNodeChange(heapnode **root, station *change, int newLength) {
	//change->lengthSum = newLength;
	//heapNodeInsert(root, change);
	//heapnode *temp = *root;
	return recursiveHeapSearch(root, root, change, newLength);
}


