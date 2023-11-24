#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int val;
	struct Node* next;
} TNode;

void pushEnd(TNode** head, int data) {
	TNode* tmp = (TNode*)malloc(sizeof(TNode));

	if (tmp == NULL) {
		return;
	}
	tmp->next = NULL;

	TNode* curr = (*head);
	if (curr == NULL) {
		tmp->val = data;
		(*head) = tmp;
	}
	else {
		for (; curr; curr = curr->next) {
			if (curr->next == NULL) {
				tmp->val = data;
				curr->next = tmp;
				return;
			}
		}
	}
}

int listCIN(TNode** head) {
	int tmp;
	char ch;

	while (1) {
		if (!scanf("%d%c", &tmp, &ch)) {
			printf("invalid input");
			return 0;
		}
		pushEnd(head, tmp);
		if (ch == '.') {
			break;
		}
	}
	return 1;
}

TNode* listFindPrevMin(TNode* head) {
	TNode* curr = head, * minEl = head;

	// finding minimal element (minEl)
	for (; curr; curr = curr->next) {
		if (curr->val < minEl->val) {
			minEl = curr;
		}
	}
	// finding an element before minEl
	for (curr = head; curr; curr = curr->next) {
		//minEl is head
		if (curr == minEl) {
			return NULL;
		}
		if (curr->next == minEl) {
			return curr;
		}
	}
}

void listCMAKE(TNode** headIN, TNode** headOUT) {
	TNode* tmp = NULL;
	if ((*headIN) == NULL) {
		return;
	}

	for (TNode* curr = (*headIN); curr;) {
		curr = (*headIN);
		if (curr == NULL) {
			break;
		}

		TNode* prevMinEl = listFindPrevMin(curr);

		//shifting minEl
		if (prevMinEl != NULL) { // if minEl in the middle of list
			if (prevMinEl->next->val >= 0) { // if minEl >= 0
				break;
			}
			tmp = prevMinEl->next->next;
			//moving minEl to new list
			if ((*headOUT) == NULL) { // if new list empty
				prevMinEl->next->next = NULL;
				(*headOUT) = prevMinEl->next;
				prevMinEl->next = tmp;
			}
			else { // if new list not empty
				for (TNode* currOUT = (*headOUT); currOUT; currOUT = currOUT->next) {
					if (currOUT->next == NULL) {
						prevMinEl->next->next = NULL;
						currOUT->next = prevMinEl->next;
						prevMinEl->next = tmp;
						break;
					}
				}
			}
		}
		else {// if minEl in the head of list
			if (curr->val >= 0) {
				break;
			}
			tmp = curr->next;

			if ((*headOUT) == NULL) {
				(*headIN)->next = NULL;
				(*headOUT) = (*headIN);
				(*headIN) = tmp;
			}
			else {
				for (TNode* currOUT = (*headOUT); currOUT; currOUT = currOUT->next) {
					if (currOUT->next == NULL) {
						(*headIN)->next = NULL;
						currOUT->next = (*headIN);
						(*headIN) = tmp;
						break;
					}
				}
			}
		}
	}
}

void listCOUT(const TNode* head) {
	if (head == NULL) {
		return;
	}

	for (int i = 1; head; head = head->next, i++) {
		printf("\nList No. %d\n", i);
		printf("value: %d\n", head->val);
		//printf("address: %p\n\n", (void*)head);
	}
}

void listFree(TNode** head) {
	if ((*head) == NULL) {
		return;
	}

	TNode* prev = NULL;
	for (; (*head)->next; ) {
		prev = (*head);
		(*head) = (*head)->next;
		free(prev);
	}

	free((*head));
}

int main() {
	TNode* listIN = NULL;
	TNode* listOUT = NULL;

	printf("enter list items, end the entry with a '.'\n");
	if (!listCIN(&listIN)) {
		return;
	}

	printf("\ninput before\n");
	listCOUT(listIN);

	listCMAKE(&listIN, &listOUT);

	printf("\ninput after\n");
	listCOUT(listIN);

	printf("\noutput\n");
	listCOUT(listOUT);

	listFree(&listIN);
	listFree(&listOUT);
}