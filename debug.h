// debug functions
void displaypath(list **listRoot);
void printTestCases(list **listRoot, char *inputfile);
int showHeapContent(heapnode *left, heapnode *right);

int showHeapContent(heapnode *left, heapnode *right) {
	int counterLeft = 0;
	int counterRight = 0;
	if(left != NULL) {
		counterLeft = showHeapContent(left->left, left->right) + 1;
	}
	if(right != NULL) {
		counterRight = showHeapContent(right->left, right->right) + 1;
	}
	if(left != NULL && left->halt != NULL) {
		fprintf(stdout, "%i. %s(%i)\n", counterLeft, left->halt->name, left->halt->lengthSum);
	}
	if(right != NULL && right->halt != NULL) {
		fprintf(stdout, "%i. %s(%i)\n", counterRight, right->halt->name, right->halt->lengthSum);
	}
	if(counterLeft < counterRight)
		return counterLeft;
	else
		return counterRight;
}


void displaypath(list **listRoot)
{
	list *listNode = *listRoot;
	int counter = 0;
	fprintf(stdout,"read-process launched\n");
	while(listNode != NULL)
	{
		fprintf(stdout,"length: %d\tmark: %s\tname: %s\n", listNode->p->length, listNode->p->mark, listNode->p->halt->name);
		counter++;
		path *temp = listNode->p->next;
		while(temp != NULL) {
		fprintf(stdout,"\tlength: %d\tmark: %s\tname: %s\n", temp->length, temp->mark, temp->halt->name);
			temp = temp->next;
		}
		listNode = listNode->next;
	}
	fprintf(stdout,"\nInsgesamt sind es %d Stationen\n", counter);
}

void printTestCases(list **listRoot, char *inputfile) {
	list *list1 = *listRoot;
	list *list2 = *listRoot;
	while(list1 != NULL) {
		while(list2 != NULL) {
			fprintf(stdout, "echo -e \"%s\\n%s\\n\" | %s %s 1> /dev/null\n", list1->p->halt->name, list2->p->halt->name, programname, inputfile);
			list2 = list2->next;
		}
		list1 = list1->next;
		list2 = *listRoot;
	}
}


