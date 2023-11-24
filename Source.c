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

int listPop(TNode** head) {
	int retVal;
	TNode* nextNode = NULL;

	if ((*head) == NULL) {
		return 0;
	}

	nextNode = (*head)->next;
	retVal = (*head)->val;
	free(*head);
	(*head) = nextNode;

	return retVal;
}

TNode* listFindPrevMin(TNode* head) {
	TNode* curr = head, * tmp = head;

	for (; curr; curr = curr->next) {
		if (curr->val < tmp->val) {
			tmp = curr;
		}
	}
	for (curr = head; curr; curr = curr->next) {
		if (curr == tmp) {
			return NULL;
		}
		if (curr->next == tmp) {
			head = curr; 
			break;
		}
	}

	return head;
}

void listDelNth(TNode** head, TNode* delEl) {
	if ((*head) == delEl) {
		listPop(head);
	}
	else {
		TNode* prev = (*head), * curr = (*head)->next;

		for (; prev; curr = curr->next, prev = prev->next) {
			if (curr == delEl) {
				prev->next = curr->next;
				free(curr);
				break;
			}
		}
	}
}

void listCMAKE(TNode** headIN, TNode** headOUT) {
	TNode* tmp = NULL;
	if ((*headIN) == NULL) {
		return;
	}

	for (TNode* curr = (*headIN); curr; curr = curr->next) {
		curr = (*headIN);
		if (curr == NULL) {
			break;
		}

		TNode* prevMinEl = listFindPrevMin(curr);
		if (prevMinEl != NULL) {
			if (prevMinEl->next->next){
				tmp = prevMinEl->next->next;

				if ((*headOUT) == NULL) {
					prevMinEl->next->next = NULL;
					(*headOUT) = prevMinEl->next;
					prevMinEl->next = tmp;
				}
				else {
					for (TNode* currOUT = (*headOUT); currOUT; currOUT = currOUT->next) {
						if (currOUT->next == NULL) {
							currOUT->next = prevMinEl->next;
							prevMinEl->next = tmp;
							break;
						}
					}
				}
			}
			else {
				if ((*headOUT) == NULL) {
					(*headOUT) = prevMinEl->next;
					prevMinEl->next = NULL;
				}
				else {
					for (TNode* currOUT = (*headOUT); currOUT; currOUT = currOUT->next) {
						if (currOUT->next == NULL) {
							currOUT->next = prevMinEl->next;
							prevMinEl->next = NULL;
							break;
						}
					}
				}
			}
		}
		else {
			if (curr->next) {
				tmp = curr->next;

				if ((*headOUT) == NULL) {
					curr->next = NULL;
					(*headOUT) = curr;
					curr = tmp;
				}
				else {
					for (TNode* currOUT = (*headOUT); currOUT; currOUT = currOUT->next) {
						if (currOUT->next == NULL) {
							currOUT->next = prevMinEl->next;
							prevMinEl->next = tmp;
							break;
						}
					}
				}
			}
			else {
				if ((*headOUT) == NULL) {
					(*headOUT) = prevMinEl->next;
					prevMinEl->next = NULL;
				}
				else {
					for (TNode* currOUT = (*headOUT); currOUT; currOUT = currOUT->next) {
						if (currOUT->next == NULL) {
							currOUT->next = prevMinEl->next;
							prevMinEl->next = NULL;
							break;
						}
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

	for (int i = 0; head; head = head->next, i++) {
		printf("List No. %d\n", i);
		printf("value: %d\n", head->val);
		printf("address: %p\n\n", (void*)head);
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