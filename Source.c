#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define N 20

typedef struct Node {
	int val;
	struct Node* next;
} TNode;

int intInput(int* size) {
	int size_n = 0;
	if (!scanf_s("%d", &size_n) || size_n > N || size_n < 0) {
		return 0;
	}
	*size = size_n;
	return 1;
}

int listCIN(TNode** head, int size_n) {
	int tmp;
	for (int i = 0; i < size_n; i++) {
		if (!scanf_s("%d", &tmp)) {
			return 0;
		}
		//pushStart((head), tmp);
	}
	return 1;
}

void pushStart(TNode** head, int data) {
	TNode* tmp = malloc(sizeof(TNode));
	if (tmp == NULL) {
		return;
	}

	tmp->val = data;
	tmp->next = (*head);
	(*head) = tmp;
}

int findFirstOverlap(TNode* head, int overlapVal) {
	if (head == NULL) {
		return -2; // список пустой
	}

	int i = 0;
	while (head->next) {
		if (head->val == overlapVal) {
			return i;
		}
		i++;
		head = head->next;
	}
	return -1; // значение не найдено
}

int delByVal(TNode** head, int delVal) {
	TNode* curr, * prev;

	if ((*head) == NULL) {
		return -2; // список пустой
	}

	if ((*head)->val == delVal) {
		return pop(head);
	}

	prev = (*head);
	curr = (*head)->next;
	while (curr) {
		if (curr->val == delVal) {
			prev->next = curr->next;
			free(curr);
			return delVal;
		}
		prev = curr;
		curr = curr->next;
	}
	return -1;
}

int pop(TNode** head) {
	int retVal = -1;
	TNode* nextNode = NULL;

	nextNode = (*head)->next;
	retVal = (*head)->val;
	free(*head);
	(*head) = nextNode;

	return retVal;
}

void listCOUT(TNode* head) {
	if (head == NULL) {
		return;
	}

	int i = 0;
	while (head->next != NULL) {
		printf("List No. %d\n", i);
		printf("value: %d\n", head->val);
		printf("address: %p\n", (void*)head->next);
		printf("\n");
		head = head->next;
		i++;
	}
}

int main() {
	int n;
	TNode* listIN = (TNode*)malloc(sizeof(TNode));
	if (listIN == NULL) return 1;
	listIN->next = NULL;

	TNode* listOUT = (TNode*)malloc(sizeof(TNode));
	if (listOUT == NULL) return 1;
	listOUT->next = NULL;

	printf("create a list of how many elements?\n");
	if (!intInput(&n)) {
		printf("invalid list size");
		return;
	}

	//listCIN(&head, n);
	int tmp;
	for (int i = 0; i < n; i++) {
		if (!scanf_s("%d", &tmp)) {
			printf("You entered not a integer");
			return 0;
		}
		pushStart(&listIN, tmp);
	}

	/*TNode* currEl = listIN;
	while (currEl->next != NULL) {
		int currVal = currEl->val;
		if (currVal < 0) {
			pushStart(&listOUT, currVal);
		}
		currEl = currEl->next;
	}*/
	TNode* currEl = listIN->next;
	while (1) {
		if (currEl->next != NULL) {
			int currVal = currEl->val;
			if (currVal < 0) {
				pushStart(&listOUT, currVal);
			}
			currEl = currEl->next;
		}
	}
	printf("%d", findFirstOverlap(listIN, -1));
	delByVal(&listIN, findFirstOverlap(listIN, -1));

	printf("\ninput\n");
	listCOUT(listIN);
	printf("\noutput\n");
	listCOUT(listOUT);

	return 0;
}