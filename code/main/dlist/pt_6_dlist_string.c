
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dlist.h"

#define MAX_STR_LEN 20

/*
    Print DList
*/

static void print_dlist (const DList *dlist){
    DListNode *node;
    int i, j;
    char *data;

    fprintf(stdout, "DList size is %d\n", dlist_size(dlist));

    i = 0;
    node = dlist_head(dlist);

    while(1){
        data = dlist_data(node);
        fprintf(stdout, "dlist.node[%03d]=%s", i, data);

        for(j = 0; j < MAX_STR_LEN - strlen(data); j++)
            fprintf(stdout, " ");

        fprintf(stdout, "| %p <- %p -> %p \n", node->prev, node, node->next);

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

    int i, j, r_num;
    char *data;

    srand(time(NULL));

    fprintf(stdout, "\nStarting program\n\n");

    // Initialize the linked dlist
    dlist_init(&dlist, free);

    if(argc <= 1){
        fprintf(stdout, "No arguments were provided");
        return 0;
    }

    // Fill the linked dlist
    for(i = 1; i < argc; i++) {

        if(i!=1 && i!=2){
            node = dlist_next(node);
        }
        else{
            node = dlist_head(&dlist);
        }

        if ((data = (char *)malloc(sizeof(char) * strlen(argv[i]))) == NULL)
            return 1;

        strcpy(data, argv[i]);
        
        if (dlist_ins_next(&dlist, node, data) != 0)
            return 1;
    }

    print_dlist(&dlist);

    // Inserting 4 nodes at random positions
    for(i = 0; i < 4; i++){
        r_num = rand() % MAX_STR_LEN;
        
        if ((data = (char *)malloc(sizeof(char) * (r_num + 1))) == NULL)
                return 1;

        for(j = 0; j < r_num; j++)
            data[j] = (char )(rand() % 26 + 65); // Adding A-Z characters to the String
        
        data[r_num]='\0'; // Adding NULL character to the String
        r_num = rand() % dlist_size(&dlist); // Randomly choosing a position
        fprintf(stdout, "\n\nInserting %s in position %03d\n", data, r_num);

        node = dlist_head(&dlist);

        if(r_num != 0){
            for(j = 0; j < r_num-1; j++)
                node = dlist_next(node);
            
            if(dlist_ins_next(&dlist, node, data) != 0)
                return 1;
        }
        else{
            if(dlist_ins_prev(&dlist, node, data) != 0)
                return 1;
        }

        print_dlist(&dlist);
    }

    // Deleting 4 nodes from random positions
    for(i = 0; i < 4; i++){
        r_num = rand() % dlist_size(&dlist); // Randomly choosing a position

        fprintf(stdout, "\n\nDeleting node in position %03d\n", r_num);

        node = dlist_head(&dlist);

        if(r_num != 0){
            for(j = 0; j < r_num-1; j++)
                node = dlist_next(node);
        }

        if(dlist_remove(&dlist, node, (void**)&data) != 0)
            return 1;

        print_dlist(&dlist);
    }

    // Destroying the dlist
    fprintf(stdout, "\nDestroying the dlist\n");
    dlist_destroy(&dlist);

    return 0;
}
