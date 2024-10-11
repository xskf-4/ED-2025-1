/*
    cdlist.c
*/
#include <stdlib.h>
#include <string.h>

#include "cdlist.h"

/*
    Initialize the cdlist
*/
void cdlist_init(CDList *list, void (*destroy)(void *data)) {
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;

    return;
}

/*
    Destroying the cdlist
*/
void cdlist_destroy(CDList *list) {
    void *data;

    while(cdlist_size(list) > 0) {
        if(cdlist_remove(list, cdlist_head(list), (void **)&data) == 0 && list->destroy != NULL) {
            list->destroy(data);
        }
    }
    memset(list, 0, sizeof(CDList));
    return;
}

/*
    Insert next node at the cdlist
*/
int cdlist_ins_next(CDList *list, CDListNode *node, const void *data) {
    CDListNode *new_node;

    //Do not allow a NULL node unless the list is empty
    if(node == NULL && cdlist_size(list) != 0)
        return -1;
    
    if((new_node = (CDListNode *)malloc(sizeof(CDListNode))) == NULL)
        return -1;

    new_node->data = (void *)data;

    if(cdlist_size(list) == 0) {
        new_node->next = new_node;
        new_node->prev = new_node;
        list->head = new_node;
        
    } else {
        new_node->next = node->next;
        new_node->prev = node;
    
        node->next->prev = new_node;
        node->next = new_node;
    }

    list->size ++;

    return 0;
}

/*
    Insert prev node at the List
*/
int cdlist_ins_prev(CDList *list, CDListNode *node, const void *data){
    CDListNode *new_node;

    //Do not allow a NULL node unless the list is empty
    if(node == NULL && cdlist_size(list) != 0)
        return -1;
    
    if((new_node = (CDListNode *)malloc(sizeof(CDListNode))) == NULL)
        return -1;

    new_node->data = (void *)data;

    // The list is empty, insert at the head
    if(cdlist_size(list) == 0) {
        new_node->next = new_node;
        new_node->prev = new_node;
        list->head = new_node;
    } else {
        new_node->next = node;
        new_node->prev = node->prev;

        node->prev->next = new_node;
        node->prev = new_node;

        // The node is the head, change head
        if(node == cdlist_head(list))
            list->head = new_node;
    }

    list->size ++;

    return 0;
}

int cdlist_remove(CDList *list, CDListNode *node, void **data){
    
    // Check if is not empty the list or node is NULL
    if(node == NULL || cdlist_size(list) == 0)
        return -1;

    *data = node->data;
    
    if(cdlist_size(list) == 1){
        node->next = NULL;
        node->prev = NULL;
    } else {
        // Removing at the head changes the head
        if(node == cdlist_head(list))
            list->head = node->next;

        node->next->prev = node->prev;
        node->prev->next = node->next;
    }

    free(node);
    list->size --;
    return 0;
}