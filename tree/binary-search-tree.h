#ifndef BST_H
#define BST_H

typedef struct BSTree BSTree;

BSTree* BSTree_create();
void BSTree_iterate(BSTree*, void (*)(void*));
void BSTree_insert(BSTree*, void*, int (*)(void*, void*));
void BSTree_destory(BSTree*);
int BSTree_find(BSTree*, void*);
void BSTree_remove(BSTree*, void*);

#endif
