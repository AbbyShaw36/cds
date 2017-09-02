#ifndef ARRAYLIST_H
#define ARRAYLIST_H

typedef struct ArrayList ArrayList;

ArrayList* ArrayList_create(int);
void ArrayList_iterate(ArrayList*, void (*)(void*));
int ArrayList_isEmpty(ArrayList*);
int ArrayList_isFull(ArrayList*);
int ArrayList_find(ArrayList*, void*);
void ArrayList_insert(ArrayList*, int, void*);
void ArrayList_remove(ArrayList*, void*);
void ArrayList_destory(ArrayList*);
void* ArrayList_head(ArrayList*);
void ArrayList_popHead(ArrayList*);

void ArrayList_pushHead(ArrayList*, void*);
void ArrayList_pushTail(ArrayList*, void*);

#endif
