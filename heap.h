

// insert new node in heap
heapnode *heapNodeInsert(heapnode **root, station *insert);
// return the smallest node (station with minimal distance)
station *heapNodeRemove(heapnode **root);
// change the value of one node and rearrange the heap
void heapNodeChange(heapnode **root, station *change, int newLength);
heapnode *mergeHeaps(heapnode **S, heapnode *Q);

heapnode *heapNodeInsert(heapnode **root, station *insert) {
	heapnode *newNode = (heapnode *)malloc(sizeof(heapnode));
	// initialize heapnode
	newNode->halt = insert;
	newNode->dist = 1;
	newNode->left = NULL;
	newNode->right = NULL;

	if(root == NULL)
		fprintf(stdout, "%s\n", newNode->halt->name);
	else
		//fprintf(stdout, "ROOT!=NULL, %s, %s\n", *root->halt->name, newNode->halt->name);
	return mergeHeaps(root, newNode);
}

heapnode *mergeHeaps(heapnode **S, heapnode *Q) {
	int D;
	// M1
	heapnode *R = NULL;
	heapnode *T;
	heapnode *P = *S;
	// M2
	while(1) {
		if(Q == NULL) {
			fprintf(stdout, "Q == NULL\n");
			D = (P == NULL)? 1 : P->dist;
			break;
		}
		if(P == NULL) {
			fprintf(stdout, "P == NULL\n");
			P = Q;
			D = 0;
			break;
		}
		if(P->halt->lengthSum >= Q->halt->lengthSum) {
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
		// M3
		if(R == NULL) {
			//fprintf(stdout, "R == NULL\n");
			*S = P;
			return P;
		}
		// M4
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

station *heapNodeRemove(heapnode **S) {
	heapnode *root = *S;
	if(root != NULL) {
		heapnode *temp = root;
		station *halt = root->halt;
		fprintf(stdout, "before merge in remove\n");
		root = mergeHeaps(root->left, root->right);
		fprintf(stdout, "before merge in remove\n");
		free(temp);
		return halt;
	}
	return NULL;
}

void heapNodeChange(heapnode **root, station *change, int newLength) {

}
