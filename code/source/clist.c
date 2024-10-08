
/*
    clist.c
*/
#include <stdlib.h>
#include <string.h>

#include "clist.h"

/*
    Initialize the clist
*/
void clist_init (CList *list, void (*destroy)(void *data)){
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;

    return;
}

/*
    Destroying the clist
*/

void clist_destroy(CList *list){
    void *data;

    while(clist_size(list) > 0){
        if (clist_rem_next(list, NULL, (void**)&data) == 0 && list->destroy != NULL){
            list->destroy(data);
        }
    }
    memset(list, 0, sizeof(list));
    return;
}

/*
    Insert next node at the clist
*/
int clist_ins_next(CList *list, CListNode *node, const void *data){
    CListNode *new_node;

    if((new_node = (CListNode *)malloc(sizeof(CListNode))) == NULL)
        return -1;

    new_node->data = (void *)data;

    if(clist_size(list) == 0){
        new_node->next = new_node;
        list->head = new_node;
    }
    else{
        if(node == NULL)
            node = list->head;

        new_node->next = node->next;
        node->next = new_node;
    }

    list->size++;

    return 0;
}

/*
    Remove node at the List
*/
int clist_rem_next (CList *list, CListNode *node, void **data){
    CListNode *old_node;

    //Check if is not empty list
    if(node == NULL && clist_size(list) == 0)
        return -1;

    if(node->next == node){
        *data = list->head->data;
        old_node = node;
        list->head = NULL;
    } else {
        if(node == NULL)
            node = list->head;
        
        *data = node->next->data;
        old_node = node->next;
        node->next = old_node->next;

        if(old_node == clist_head(list))
            list->head = node->next;
    }

    free(old_node);
    list->size --;

    return 0;
}
