#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int val;
	struct Node* next;
} TNode;

int pushStart(TNode** head, int data) {
	TNode* tmp = (TNode*)malloc(sizeof(TNode));

	if (tmp == NULL) {
		return 0;
	}

	tmp->val = data;
	tmp->next = (*head);
	(*head) = tmp;
	return 1;
}

int listCIN(TNode** head) {
	int tmp;

	while (1) {
		if (!scanf("%d", &tmp)) {
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


TNode* listFindMin(TNode* head) {
	TNode* nextEL = NULL;

	for (nextEL = head->next; nextEL; nextEL = nextEL->next) {
		if (nextEL->val < head->val) {
			head = nextEL;
			break;
		}
	}

	return head;
}

void listDelEl(TNode** head, TNode* delEl) {
	TNode* prev = NULL;
	TNode* curr = (*head);

	while (1) {
		if (curr == delEl && prev == NULL) {
			prev = curr;
			curr = curr->next;
			free(prev);
			break;
		}
		if (curr == delEl && prev != NULL){
			prev->next = curr->next; 
			free(curr); 
			break;
		}
		prev = curr;
		curr = curr->next;
		if (curr == NULL) {
			break;
		}
	}
}

int listCMAKE(TNode** headIN, TNode** headOUT) {
	if (headIN == NULL) {
		return 0;
	}

	TNode* curr = (*headIN);
	while (1) {
		if (curr == NULL){
			break;
		}
		TNode* minEl = listFindMin(curr);
		if (minEl->val < 0) {
			pushStart(headOUT, minEl->val);
			listDelEl(headIN, minEl);
		}
		else {
			curr = curr->next;
			if (curr == NULL)
			{
				break;
			}
		}
	}
	return 1;
}

int listSort(TNode** head) {
	if (head == NULL) {
		return 0;
	}

	TNode* curr = (*head);
	for (; curr; curr = curr->next) {
		TNode* minEl = listFindMin(curr);

		if (minEl != curr) {
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
	for (; head; head = head->next, i++) {
		printf("\nList No. %d\n", i);
		printf("value: %d\n", head->val);
		printf("address: %p\n\n", (void*)head);
	}
	return 1;
}

int listFree(TNode** head) {
	if (head == NULL) {
		return 0;
	}

	TNode* prev = NULL;
	TNode* curr = (*head);
	for (; curr->next; curr = curr->next) {
		prev = curr;
		free(prev);
	}
	free(curr);

	return 1;
}

int main() {
	TNode* listIN = NULL;
	TNode* listOUT = NULL;

	printf("input list elements, end input by .\n");
	listCIN(&listIN);

	listCMAKE(&listIN, &listOUT);
	listSort(&listOUT);

	printf("\ninput\n");
	listCOUT(listIN);

	printf("\noutput\n");
	listCOUT(listOUT);

	listFree(&listIN);
	listFree(&listOUT);
}