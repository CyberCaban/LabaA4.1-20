#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int val;
	struct Node* next;
} TNode;

void pushStart(TNode** head, int data) {
	TNode* tmp = malloc(sizeof(TNode));
	if (tmp == NULL) {
		return;
	}

	tmp->val = data;
	tmp->next = (*head);
	(*head) = tmp;
}

void pushEnd(TNode** head, int data) {
	TNode* tmp = malloc(sizeof(TNode));
}

void pop(TNode** head) {
	TNode* tmp = (*head);

	if (tmp->next != NULL) {
		printf("%d\n", tmp->next);
	}
}

TNode* listCOUT(TNode* head) {
	if (head == NULL) {
		return;
	}

	while (head->next) {
		printf("value: %d\n", head->val);
		printf("address: %p\n", (void*)head->next);
		printf("\n");
		head = head->next;
	}
}

int main() {
	TNode* head = NULL;
	head = (TNode*)malloc(sizeof(TNode));

	if (head == NULL) {
		return 1;
	}
	head->next = NULL;

	pushStart(&head, 20);
	pushStart(&head, 32);
	pushStart(&head, 55);

	//pop(&head);

	listCOUT(head);

	return 0;
}