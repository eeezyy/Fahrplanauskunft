// insert new node in heap
heapnode *heapNodeInsert(heapnode **root, station *insert, int value, station *prev);
// return the smallest node (station with minimal distance)
heapnode *heapNodeRemove(heapnode **heapAddress);
// core function for heap, merges two heap trees, returns the root node
// normaly used to add a node to heap tree
heapnode *mergeHeaps(heapnode **heapAddress, heapnode *Q);
heapnode *mergeHeaps2(heapnode *heapAddress, heapnode *Q);
station *searchHeapNode(heapnode *left, heapnode *right, station *halt);

heapnode *heapNodeInsert(heapnode **root, station *insert, int value, station *prev) {
	heapnode *newNode = (heapnode *)malloc(sizeof(heapnode));
	// initialize new heapnode
	newNode->halt = insert;
	newNode->dist = 1;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->value = value;
	newNode->prev = prev;
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
		if(P->value < Q->value) {
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

heapnode *heapNodeRemove(heapnode **heapAddress) {
	if(heapAddress != NULL) {
		if(*heapAddress != NULL) {
			heapnode *root = *heapAddress;
			heapnode *temp = root;
			station *halt = root->halt;
			halt->lengthSum = root->value;
			halt->prev = root->prev;
			// write new node to root
			*heapAddress = mergeHeaps(&(*heapAddress)->left, root->right);
			//free(temp);
			// return removed node
			return temp;
		}
	}
	return NULL;
}

heapnode *checkHeapSort(heapnode *left, heapnode *right, station *halt) {
	heapnode *foundNodeLeft = NULL;
	heapnode *foundNodeRight = NULL;
	// recursive search, left and right node
	if(left != NULL && left->halt != NULL) {
		if(left->halt == halt) {
			return left;
		}
		foundNodeLeft = checkHeapSort(left->left, left->right, halt);
	}
	if(right != NULL && right->halt != NULL) {
		if(right->halt == halt) {
			return right;
		}
		foundNodeRight = checkHeapSort(right->left, right->right, halt);
	}
	// when found, remove node
	if(foundNodeLeft != NULL || foundNodeRight != NULL) {
		if(foundNodeLeft != NULL) {
			heapnode *tempMerge = mergeHeaps2(foundNodeLeft->left, foundNodeLeft->right);
			if(left->left != NULL && halt == left->left->halt) {
				left->left = tempMerge;
			} else {
				left->right = tempMerge;
			}
			free(foundNodeLeft);
		} else {
			heapnode *tempMerge = mergeHeaps2(foundNodeRight->left, foundNodeRight->right);
			if(right->left != NULL && halt == right->left->halt) {
				right->left = tempMerge;
			} else {
				right->right = tempMerge;
			}
			free(foundNodeRight);
		}
	}
	
	return NULL;
}

heapnode *mergeHeaps2(heapnode *P, heapnode *Q) {
	int D;
	// initialize
	heapnode *R = NULL;
	heapnode *T;

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
		if(P->value < Q->value) {
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

station *searchHeapNode(heapnode *left, heapnode *right, station *halt) {
	station *foundNodeLeft = NULL;
	station *foundNodeRight = NULL;
	// recursive search, left and right node
	if(left != NULL && left->halt != NULL) {
		if(left->halt == halt) {
			return left->halt;
		}
		foundNodeLeft = searchHeapNode(left->left, left->right, halt);
	}
	if(right != NULL && right->halt != NULL && foundNodeLeft == NULL) {
		if(right->halt == halt) {
			return right->halt;
		}
		foundNodeRight = searchHeapNode(right->left, right->right, halt);
	}
	// when found, remove node
	if(foundNodeLeft != NULL || foundNodeRight != NULL) {
		if(foundNodeLeft != NULL) {
			return foundNodeLeft;
		} else {
			return foundNodeRight;
		}
	}
	
	return NULL;
}

