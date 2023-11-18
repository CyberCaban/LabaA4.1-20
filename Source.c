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

int pushStart(TNode** head, int data) {
	TNode* tmp = malloc(sizeof(TNode));

	if (tmp == NULL) {
		return 0;
	}

	tmp->val = data;
	tmp->next = (*head);
	(*head) = tmp;
	return 1;
}

int listCIN(TNode** head, int size_n) {
	int tmp;

	for (int i = 0; i < size_n; i++) {
		if (!scanf_s("%d", &tmp)) {
			return 0;
		}
		pushStart(head, tmp);
	}
	return 1;
}

int listFindFirstOverlap(const TNode* head, int overlapVal) {
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

int listDelByVal(TNode** head, int delVal) {
	TNode* curr, * prev;

	if (head == NULL) {
		return; // список пустой
	}

	if ((*head)->val == delVal) {
		return listPop(head);
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
	return;
}

int listPop(TNode** head) {
	int retVal = -1;
	TNode* nextNode = NULL;

	nextNode = (*head)->next;
	retVal = (*head)->val;
	free(*head);
	(*head) = nextNode;

	return retVal;
}

int listCMAKE(const TNode* headIN, TNode** headOUT) {
	TNode* curr;
	if (headIN == NULL){
		return 0;
	}

	while (headIN){
		if (headIN->val < 0){
			pushStart(headOUT, headIN->val);
		}

		headIN = headIN->next;
	}
	return 1;
}

TNode* listFindMin(TNode* head) {
	TNode* next = NULL;

	for (next = head->next; next; next = next->next){
		if (next->val < head->val) {
			head = next;
		}
	}

	return head;
}

int listSort(TNode** head) {
	if (head == NULL) {
		return 0;
	}

	TNode* curr = (*head);
	for (; curr; curr = curr->next) {
		TNode* minEl = listFindMin(curr);

		if (minEl != curr){
			int tmp = curr->val;
			curr->val = minEl->val;
			minEl->val = tmp;
		}
	}
	return 1;
}

int listCOUT(const TNode* head) {
	if (head == NULL) {
		return 0;
	}

	int i = 0;
	while (head) {
		printf("List No. %d\n", i);
		printf("value: %d\n", head->val);
		printf("address: %p\n", (void*)head);
		printf("\n");
		head = head->next;
		i++;
	}
	return 1;
}

int listFree(TNode** head) {
	if (head == NULL) {
		return 0;
	}

	TNode* prev = NULL;
	TNode* curr = (*head);
	while (curr->next){
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(curr);

	return 1;
}

int main() {
	int n;
	TNode* listIN = NULL;
	TNode* listOUT = NULL;

	printf("create a list of how many elements?\n");
	if (!intInput(&n)) {
		printf("invalid list size");
		return;
	}

	printf("input list elements\n");
	listCIN(&listIN, n);

	printf("%d", listCMAKE(listIN, &listOUT));
	listSort(&listOUT);

	printf("\ninput\n");
	listCOUT(listIN);

	printf("\noutput\n");
	listCOUT(listOUT);

	listFree(&listIN);
	listFree(&listOUT);

	return;
}