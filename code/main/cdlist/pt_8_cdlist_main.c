
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cdlist.h"

/*
    Print CDList
*/

static void print_cdlist(const CDList *cdlist) {
    CDListNode *node;
    int i, *data;

    fprintf(stdout, "CDList size is %d\n", cdlist_size(cdlist));
    node = cdlist_head(cdlist);

    /*
        print info for each node
    */

    for(i = 0; i < cdlist_size(cdlist); i++){
        data = cdlist_data(node);
        fprintf(stdout, "cdlist.node[%03d]=%03d | %p <- %p -> %p\n", i, *data, node->prev, node, node->next);
        node = cdlist_next(node);
    }

    return;
}

int main(int argc, char **argv) {
    CDList cdlist;
    CDListNode *node;

    int i, j, r_num;
    int *data;

    srand(time(NULL));

    fprintf(stdout, "\nStarting program\n\n");

    //Initialize the circular double linked list
    cdlist_init(&cdlist, free);

    if(argc <= 1) {
        fprintf(stdout, "No arguments were provided");
        return 0;
    }

    // Fill the circular list
    for(i = 1; i < argc; i++) {
        if(i != 1 && i != 2)
            node = cdlist_next(node);
        else
            node = cdlist_head(&cdlist);

        if((data = (int *)malloc(sizeof(int))) == NULL)
            return 1;

        *data = atoi(argv[i]);

        if(cdlist_ins_next(&cdlist, node, data) != 0)
            return 1;
    }

    print_cdlist(&cdlist);

    // Adding 4 random elements at random position by using cdlist_ins_next
    for(i = 0; i < 4; i++) {
        r_num = rand() % 1000;

        if((data = (int *)malloc(sizeof(int))) == NULL)
            return -1;

        *data = r_num;
        r_num = rand() % cdlist_size(&cdlist);
        fprintf(stdout, "\n\nAdding %03d in position %03d\n", *data, r_num);

        node = cdlist_head(&cdlist);

        if(r_num != 0) {
            for(j = 0; j< r_num-1; j++)
                node = cdlist_next(node);

            if(cdlist_ins_next(&cdlist, node, data) != 0)
                return 1;
            
        } else {
            if(cdlist_ins_prev(&cdlist, node, data) != 0)
                return 1;
        }

        print_cdlist(&cdlist);
    }

    // Destroying cdlist
    fprintf(stdout, "\n\nDestroying the cdlist\n");
    cdlist_destroy(&cdlist);
    return 0;
}
