// insert new node in heap
heapnode *heapNodeInsert(heapnode **root, station *insert);
// return the smallest node (station with minimal distance)
station *heapNodeRemove(heapnode **heapAddress);
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
		// if new heap/heapnode is NULL
		if(Q == NULL) {
			D = (P == NULL)? 1 : P->dist;
			break;
		}
		// if root heap is NULL set new heap/heapnode as root heap
		if(P == NULL) {
			P = Q;
			D = 0;
			break;
		}
		// compare which node is smaller
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
	if(heapAddress != NULL) {
		if(*heapAddress != NULL) {
			heapnode *root = *heapAddress;
			heapnode *temp = root;
			station *halt = root->halt;
			// write new node to root
			*heapAddress = mergeHeaps(&(*heapAddress)->left, root->right);
			free(temp);
			// return removed node
			return halt;
		}
	}
	return NULL;
}

