
#include <stdio.h>
#include <stdlib.h>

#include "dlist.h"

static void print_dlist (const DList *dlist){
    DListNode *node;
    int *data, i;

    fprintf(stdout, "DList size s %d\n", dlist_size(dlist));

    i=0;
    node = dlist_head(dlist);

    while(1){
        data = dlist_data(node);
        fprintf(stdout, "dlist.node[%03d]=%03d, %p <- %p -> %p \n", i, *data, node->prev, node, node->next);

        i++;

        if(dlist_is_tail(node))
            break;
        else
            node = dlist_next(node);
    }

    return;
}

int main(int argc, char **argv){
    DList dlist;
    DListNode *node;

    int *data, i;

    fprintf(stdout, "\nStarting program\n");

    // Initialize the linked dlist
    dlist_init(&dlist, free);

    // Fill the linked dlist
    for(i = 20; i > 10; i--) {
        
        if(i!=20 && i!=19){
            node = dlist_next(node);
        }
        else{
            node = dlist_head(&dlist);
        }

        if ((data = (int *)malloc(sizeof(int))) == NULL)
            return 1;

        *data = i;
        
        if (dlist_ins_next(&dlist, node, data) != 0)
            return 1;

        fprintf(stdout, "Succesfully node insertion");
    }

    print_dlist(&dlist);

    fprintf(stdout, "\nDestroying the dlist\n");
    dlist_destroy(&dlist);

    return 0;
}
