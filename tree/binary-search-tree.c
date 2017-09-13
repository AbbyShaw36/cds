#include "binary-search-tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct BSTreeNode {
	void* value;
	struct BSTreeNode* leftChild;
	struct BSTreeNode* rightChild;
} BSTreeNode;

struct BSTree {
	BSTreeNode* tree;
};

void _iterateTreeNode(BSTreeNode*, void (*)(void*));
void _destoryTreeNode(BSTreeNode*);
int _findTreeNode(BSTreeNode*, void*);
void _removeTreeNode(BSTreeNode**, void*);

BSTree* BSTree_create()
{
	BSTree* root = malloc(sizeof(BSTree));
	root->tree = NULL;

	return root;
}

void _iterateTreeNode(BSTreeNode* node, void (*fun)(void* value))
{
	if (node == NULL) {
		return;
	}

	_iterateTreeNode(node->leftChild, fun);
	fun(node->value);
	_iterateTreeNode(node->rightChild, fun);
}

void BSTree_iterate(BSTree* root, void (*fun)(void* value))
{

	_iterateTreeNode(root->tree, fun);
}

void BSTree_insert(BSTree* root, void* value, int (*cmpFn)(void* value1, void* value2))
{
	BSTreeNode* newNode = malloc(sizeof(BSTreeNode));

	newNode->value = value;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;

	if (root->tree == NULL) {
		root->tree = newNode;
		return;
	}

	BSTreeNode** node = &(root->tree);

	while (*node != NULL) {
		if (cmpFn((*node)->value, value)) {
			node = &((*node)->leftChild);
		} else {
			node = &((*node)->rightChild);
		}
	}

	*node = newNode;
}

void _destoryTreeNode(BSTreeNode* node)
{
	if (node == NULL) {
		return;
	}

	_destoryTreeNode(node->leftChild);
	_destoryTreeNode(node->rightChild);
	free(node);
}

void BSTree_destory(BSTree* root)
{
	_destoryTreeNode(root->tree);
	free(root);
}

int _findTreeNode(BSTreeNode* node, void* value)
{
	if (node == NULL) {
		return 0;
	}

	return (node->value == value) || _findTreeNode(node->leftChild, value) || _findTreeNode(node->rightChild, value);
}

int BSTree_find(BSTree* root, void* value)
{
	return _findTreeNode(root->tree, value);
}

void _removeTreeNode(BSTreeNode** node, void* value)
{
	if (*node == NULL) {
		return;
	}

	if ((*node)->value == value) {
		BSTreeNode* resNode = *node;
		BSTreeNode* leftTree = (*node)->leftChild;
		BSTreeNode* rightTree = (*node)->rightChild;

		if (rightTree == NULL) {
			*node = leftTree;
		} else {
			*node = rightTree;
			BSTreeNode** rightTree_leftNode = &(rightTree->leftChild);

			while (*rightTree_leftNode != NULL) {
				rightTree_leftNode = &(*rightTree_leftNode)->leftChild;
			}

			*rightTree_leftNode = leftTree;
		}

		printf("-%d\n", *(int*)resNode);
		free(resNode);
	}

	_removeTreeNode(&(*node)->leftChild, value);
	_removeTreeNode(&(*node)->leftChild, value);
}

void BSTree_remove(BSTree* root, void* value)
{
	_removeTreeNode(&root->tree, value);
}
