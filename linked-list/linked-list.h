#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct LinkedList LinkedList;

LinkedList* LinkedList_create();
int LinkedList_isEmpty(LinkedList*);
void LinkedList_iterate(LinkedList*, void (*)(void*));
void LinkedList_destory(LinkedList*);
void LinkedList_insert(LinkedList*, int, void*);
void LinkedList_remove(LinkedList*, void*);
void LinkedList_popHead(LinkedList*);
void* LinkedList_head(LinkedList*);

void LinkedList_pushHead(LinkedList*, void*);

void LinkedList_pushTail(LinkedList*, void*);

#endif
