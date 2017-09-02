#include "array-list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct ArrayList {
	void** list;
	int maxSize;
	int size;
};

ArrayList* ArrayList_create(int maxSize)
{
	ArrayList* root = malloc(sizeof(ArrayList));

	root->list = malloc(sizeof(void*) * maxSize);
	root->maxSize = maxSize;
	root->size = 0;

	return root;
}

void ArrayList_iterate(ArrayList* root, void (*fun)(void*))
{
	int size = 0;

	while (size < root->size) {
		fun(root->list[size]);
		size++;
	}

	printf("\n");
}

int ArrayList_isEmpty(ArrayList* root)
{
	return root->size == 0;
}

int ArrayList_isFull(ArrayList* root)
{
	return root->size == root->maxSize;
}

void ArrayList_insert(ArrayList* root, int index, void* value)
{
	assert(index <= root->size && index >= 0);

	if (ArrayList_isFull(root)) {
		root->maxSize *= 2;
	}

	void** newList = malloc(sizeof(void*) * root->maxSize);
	void** oldList = root->list;

	memcpy(newList, oldList, index * sizeof(void*));
	newList[index] = value;
	memcpy(newList + index + 1, oldList + index, (root->size - index) * sizeof(void*));
	free(oldList);
	root->list = newList;
	root->size++;
}

int ArrayList_find(ArrayList* root, void* value)
{
	int i = 0;

	while (i < root->size) {
		if (root->list[i] == value) {
			return i;
		}

		i++;
	}

	return -1;
}

void ArrayList_remove(ArrayList* root, void* value)
{
	int index = ArrayList_find(root, value);

	if (index != -1) {
		void** newList = malloc(sizeof(void*) * root->maxSize);
		void** oldList = root->list;

		memcpy(newList, oldList, index * sizeof(void*));
		memcpy(newList + index, oldList + index + 1, (root->size - index - 1) * sizeof(void*));
		free(oldList);

		root->list = newList;
		root->size--;
	}
}

void ArrayList_destory(ArrayList* root)
{
	free(root->list);
	free(root);
}

void* ArrayList_head(ArrayList* root)
{
	assert(!ArrayList_isEmpty(root));

	return root->list[0];
}

void ArrayList_popHead(ArrayList* root)
{
	assert(!ArrayList_isEmpty(root));

	void** newList = malloc(sizeof(int) * root->maxSize);
	void** oldList = root->list;

	memcpy(newList, oldList + 1, (root->size - 1) * sizeof(void*));
	free(oldList);
	root->list = newList;
	root->size--;
}

void ArrayList_pushHead(ArrayList* root, void* value)
{
	if (ArrayList_isFull(root)) {
		root->maxSize *= 2;
	}

	void** newList = malloc(sizeof(int) * root->maxSize);
	void** oldList = root->list;

	newList[0] = value;
	memcpy(newList + 1, oldList, root->size * sizeof(void*));
	free(oldList);
	root->list = newList;
	root->size++;
}

void ArrayList_pushTail(ArrayList* root, void* value)
{
	if (ArrayList_isFull(root)) {
		root->maxSize *= 2;

		void** newList = malloc(sizeof(int) * root->maxSize);

		memcpy(newList, root->list, root->size * sizeof(void*));
		free(root->list);
		root->list = newList;
	}

	root->list[root->size] = value;
	root->size++;
}
