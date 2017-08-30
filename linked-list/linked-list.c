#include "linked-list.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node {
	void* value;
	struct Node* next;
	struct Node* prev;
} LinkedListNode;

struct LinkedList {
	LinkedListNode* head;
	LinkedListNode* tail;
	int size;
};

LinkedList* LinkedList_create()
{
	LinkedList* root = malloc(sizeof(LinkedList));
	root->head = NULL;
	root->tail = NULL;
	root->size = 0;
	return root;
}

void LinkedList_iterate(LinkedList* root, void (*fun)(void*))
{
	LinkedListNode *node = root->head;

	while (node != NULL) {
		fun(node->value);
		node = node->next;
	}

	printf("\n");
}

int LinkedList_isEmpty(LinkedList* root)
{
	return root->size == 0;
}

void LinkedList_destory(LinkedList* root)
{
	if (!LinkedList_isEmpty(root)) {
		LinkedListNode *node = root->head;

		while (node != NULL) {
			LinkedListNode *oldNode = node;
			node = node->next;
			free(oldNode);
		}
	}

	free(root);
	root = NULL;
}

void LinkedList_insert(LinkedList* root, int index, void* value)
{
	int size = root->size;
	LinkedListNode *newNode = malloc(sizeof(LinkedListNode));

	newNode->value = value;

	printf("size-%d\n", size);
	printf("index-%d\n", index);

	if (size == 0) {
		newNode->prev = NULL;
		newNode->next = NULL;
		root->head = newNode;
		root->tail = newNode;
	} else if (index > size-1) {
		newNode->prev = root->tail;
		newNode->next = NULL;
		root->tail->next = newNode;
		root->tail = newNode;
	} else if (index <= -size) {
		newNode->prev = NULL;
		newNode->next = root->head;
		root->head->prev = newNode;
		root->head = newNode;
	} else {
		int i;
		LinkedListNode *node;
		LinkedListNode **prevNode;

		if (index < 0) {
			i = size - 1;
			node = root->tail;

			while (i > size + index) {
				node = node->prev;
				i--;
			}

		} else {
			i = 0;
			node = root->head;

			while (i < index) {
				node = node->next;
				i++;
			}
		}

		prevNode = &node->prev;

		newNode->prev = node->prev;
		newNode->next = node;

		if (*prevNode == NULL) {
			root->head = newNode;
		} else {
			(*prevNode)->next = newNode;
		}

		*prevNode = newNode;
	}

	root->size++;
}

void LinkedList_remove(LinkedList* root, void* value)
{
	assert(!LinkedList_isEmpty(root));

	LinkedListNode *node = root->head;

	while (node != NULL) {
		if (node->value == value) {
			LinkedListNode **prevNode = &node->prev;
			LinkedListNode **nextNode = &node->next;

			if (*prevNode == NULL) {
				*prevNode = node->next;
				root->head = *prevNode;
			} else {
				(*prevNode)->next = node->next;
			}

			if (*nextNode == NULL) {
				*nextNode = node->prev;
				root->tail = *nextNode;
			} else {
				(*nextNode)->prev = node->prev;
			}

			free(node);

			return;
		}

		node = node->next;
	}

	root->size--;
}

void LinkedList_popHead(LinkedList* root)
{
	assert(!LinkedList_isEmpty(root));

	root->size--;

	LinkedListNode *headNode = root->head;

	if (root->size == 0) {
		root->head = NULL;
		root->tail = NULL;
	} else {
		root->head = headNode->next;
	}

	free(headNode);
}

void LinkedList_pushHead(LinkedList* root, void* value)
{
	LinkedListNode **headNode = &root->head;
	LinkedListNode *newNode = malloc(sizeof(LinkedListNode));

	newNode->value = value;
	newNode->next = *headNode;
	newNode->prev = NULL;
	*headNode = newNode;

	if (root->size == 0) {
		root->tail = newNode;
	}

	root->size++;
}

void LinkedList_pushTail(LinkedList* root, void* value)
{
	LinkedListNode **tailNode = &root->tail;
	LinkedListNode *newNode = malloc(sizeof(LinkedListNode));

	newNode->value = value;
	newNode->prev = *tailNode;
	newNode->next = NULL;
	(*tailNode)->next = newNode;
	*tailNode = newNode;

	if (root->size == 0) {
		root->head = newNode;
	}

	root->size++;
}

void* LinkedList_head(LinkedList* root)
{
	assert(!LinkedList_isEmpty(root));

	return root->head->value;
}
