
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "clist.h"

#define MAX_STR_LEN 20

/*
    Print CList
*/

static void print_clist(const CList *clist){
    CListNode *node;
    int i, j;
    float *data;
    char str_x[MAX_STR_LEN]; // auxiliar string

    fprintf(stdout, "CList size is %d\n", clist_size(clist));

    i = 0;
    node = clist_head(clist);

    /*
        print info for each node
    */

    for(i=0; i<clist_size(clist); i++){
        data = clist_data(node);

        snprintf(str_x, MAX_STR_LEN, "%g", *data);
        fprintf(stdout, "clist.node[%03d]=%g", i, *data);
        for(j = 0; j < MAX_STR_LEN-strlen(str_x); j++)
            fprintf(stdout, " ");

        fprintf(stdout, "| %p -> %p\n", node, node->next);
        node = clist_next(node);
    }

    return;
}

int main(int argc, char **argv){
    CList clist;
    CListNode *node;

    int i, j, r_num1, r_num2;
    float *data;

    srand(time(NULL));

    fprintf(stdout, "\nStarting program\n\n");

    //Initialize the circular list
    clist_init(&clist, free);

    if(argc <= 1){
        fprintf(stdout, "No arguments were provided");
        return 0;
    }

    //Fill the circular list
    for(i = 1; i < argc; i++){
        if(i!=1 && i!=2){
            node = clist_next(node);
        }
        else{
            node = clist_head(&clist);
        }

        if((data = (float *)malloc(sizeof(float))) == NULL)
            return 1;

        *data = atof(argv[i]);

        if(clist_ins_next(&clist, node, data) != 0)
            return 1;
    }

    print_clist(&clist);

    // Adding 4 random elements at random positions
    for(i = 0; i < 4; i++){
        r_num1 = rand() % 1000;
        r_num2 = rand() % 100+1;

        if((data = (float *)malloc(sizeof(float))) == NULL)
            return 1;

        *data = (float )r_num1 / r_num2;
        r_num1 = rand() % clist_size(&clist);
        fprintf(stdout, "\n\nInserting %g in position %03d\n", *data, r_num1);
        
        if(r_num1 == 0){
            node = NULL;
        } else {
            node = clist_head(&clist);
            for(j = 0; j < r_num1-1; j++)
                node = clist_next(node);
        }
        
        if(clist_ins_next(&clist, node, data) != 0)
            return 1;

        print_clist(&clist);
    }

    // Removing 4 random elements at random positions
    for(i = 0; i < 4; i++){
        r_num1 = rand() % clist_size(&clist); //Randomly choosing a position

        fprintf(stdout, "\n\nDeleting node in position %03d\n", r_num1);

        if(r_num1 == 0){
            node = NULL;
        } else {
            node = clist_head(&clist);
            for(j = 0; j < r_num1-1; j++)
                node = clist_next(node);
        }

        if(clist_rem_next(&clist, node, (void**)&data) != 0)
            return 1;

        print_clist(&clist);
    }

    fprintf(stdout, "\n\nDestroying the clist\n");
    clist_destroy(&clist);
    return 0;
}
