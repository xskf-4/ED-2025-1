#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "list.h"
#include "queue.h"

#define MAX_STR_LEN 20

/*
    Print queue
*/

static void print_queue(const Queue *queue) {
    ListNode *node;
    int i, j;
    char *data;

    fprintf(stdout, "Queue size is %d\n", queue_size(queue));

    i = 0;
    node = list_head(queue);

    while(i < queue_size(queue)) {
        data = list_data(node);
        fprintf(stdout, "queue[%03d]=%s | %p -> %p\n", i, data, node, node->next);
        node = list_next(node);
        i++;
    }
    return;
}

int main(int argc, char const *argv[]) {
    Queue queue;
    int i, j, r_num1, r_num2;
    char *data;

    srand(time(NULL));

    fprintf(stdout, "\nStarting program\n\n");

    // Initialize the queue
    queue_init(&queue, free);

    if(argc <= 1) {
		fprintf(stdout, "No arguments were provided");
		return 0;
	}

    fprintf(stdout, "Enqueuing %d elements\n", argc-1);
    for(i = 1; i < argc; i++){
		if ((data = (char *)malloc(sizeof(char) * MAX_STR_LEN)) == NULL)
	    	return 1;
            
        strcpy(data, argv[i]);
        for(j = strlen(data); j < MAX_STR_LEN; j++)
			strcat(data, " ");

		if (queue_enqueue(&queue, data) != 0)
	    	return 1;
	}
    print_queue(&queue);

    r_num1 = rand() % queue_size(&queue) + 1;
    fprintf(stdout, "\nDequeuing %d elements\n", r_num1);
    for(i = 0; i < r_num1; i++) {
        if(queue_dequeue(&queue, (void **)&data) == 0)
            free(data);
        else
            return 1;
    }
    print_queue(&queue);

    fprintf(stdout, "\nEnqueuing 5 random Strings:");
	for(i = 0; i < 5; i++) {
		if ((data = (char *)malloc(sizeof(char) * MAX_STR_LEN)) == NULL)
			return 1;
		
        r_num2 = rand() % MAX_STR_LEN + 1;
		for(j = 0; j < MAX_STR_LEN; j++){
            if(j < r_num2) {
                r_num1 = rand() % 26 + 65;
                data[j] = (char )r_num1;
            }
            else
                data[j] = ' ';

        }
        data[j] = '\0';

        fprintf(stdout, "\n - %s", data);

		if (queue_enqueue(&queue, data) != 0)
			return 1;
	}
    fprintf(stdout, "\n");
	print_queue(&queue);

    fprintf(stdout, "\nDestroying the queue\n");
    queue_destroy(&queue);
}


