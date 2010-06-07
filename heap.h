

// insert new node in heap
void heapNodeInsert(heapnode *root, station *insert);
// return the smallest node (station with minimal distance)
station *heapNodeRemove(heapnode *root);
// change the value of one node and rearrange the heap
void heapNodeChange(heapnode *root, station *change, int newLength);
heapnode *mergeHeaps(heapnode *P, heapnode *Q);

void heapNodeInsert(heapnode *root, station *insert) {
	heapnode *newNode = (heapnode *)malloc(sizeof(heapnode));
	// initialize heapnode
	newNode->halt = insert;
	newNode->dist = 1;
	newNode->left = NULL;
	newNode->right = NULL;

	root = mergeHeaps(root, newNode);
}

heapnode *mergeHeaps(heapnode *P, heapnode *Q) {
	int D;
	// M1
	heapnode *R = NULL;
	heapnode *T;
	// M2
	while(1) {
		if(Q == NULL) {
			D = (P == NULL)? 1 : P->dist;
			break;
		}
		if(P == NULL) {
			P = Q;
			D = 0;
			break;
		}
		if(P->halt->lengthSum >= Q->halt->lengthSum) {
			T = P->right;
			P->right = R;
			R = P;
			P = T;
		}
	}

	while(1) {
		// M3
		if(R == NULL) {
			return P;
		}
		// M4
		Q = R->right;
		if(R->left->dist < D) {
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

station *heapNodeRemove(heapnode *root) {
	heapnode *temp = root;
	station *halt = root->halt;
	root = mergeHeaps(root->left, root->right);
	free(temp);
	return halt;
}

void heapNodeChange(heapnode *root, station *change, int newLength) {

}
