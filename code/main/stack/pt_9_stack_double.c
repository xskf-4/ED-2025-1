#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "list.h"
#include "stack.h"

#define STR_LEN_MAX 20

/*
   Print stack
*/

static void print_stack(const Stack *stack) {
	ListNode *node;
	int size, i, j;
	double *data;
	char cad_aux[STR_LEN_MAX];

	fprintf(stdout, "Stack size is %d\n", size = stack_size(stack));

	i = 0;
	node = list_head(stack);

	while (i < size) {
		data = list_data(node);

		sprintf(cad_aux, "%g", *data);

		for(j = strlen(cad_aux); j < STR_LEN_MAX; j++)
			strcat(cad_aux, " ");

		fprintf(stdout, "stack[%03d]=%s | %p -> %p\n", i, cad_aux, node, node->next);
		node = list_next(node);
	 	i++;
	}
	return;
}

int main(int argc, char const *argv[]) {
	Stack stack;
	int i, r_num1, r_num2;
	double *data;

	srand(time(NULL));

	fprintf(stdout, "\nStarting program\n\n");

	// Initialize the stack
	stack_init(&stack, free);

	if(argc <= 1) {
		fprintf(stdout, "No arguments were provided");
		return 0;
	}

	fprintf(stdout, "\n\nPushing %d elements\n", argc-1);

	for(i = 1; i < argc; i++){
		if ((data = (double *)malloc(sizeof(double))) == NULL)
	    	return 1;

		*data = atof(argv[i]);

		if (stack_push(&stack, data) != 0)
	    	return 1;
	}

	print_stack(&stack);

	r_num1 = rand() % stack_size(&stack) + 1;
	fprintf(stdout, "\nPopping %d elements\n", r_num1);
	for (i = 0; i < r_num1; i++) {
		if(stack_pop(&stack, (void **)&data) == 0)
			free(data);
		else
			return 1;
	}
	print_stack(&stack);
	

	fprintf(stdout, "\nPushing 5 random numbers: [");
	for(i = 0; i < 5; i++) {
		if ((data = (double *)malloc(sizeof(double))) == NULL)
			return 1;
		
		r_num1 = rand() % 10000;
		r_num2 = rand() % 100 + 1;
		*data = (double) r_num1 / r_num2;

		if(i == 0)
			fprintf(stdout, "%g, ", *data);
		else if(i == 4)
			fprintf(stdout, " %g", *data);
		else
			fprintf(stdout, "%g, ", *data);

		if (stack_push(&stack, data) != 0)
			return 1;
	}
	fprintf(stdout, "]\n");
	print_stack(&stack);

	if ((data = stack_peek(&stack)) != NULL)
		fprintf(stdout, "\nPeeking at the top element [value]=%g\n", *data);
	else
		fprintf(stdout, "\nPeeking at the top element [value]=NULL\n");
	print_stack(&stack);

	fprintf(stdout, "\nPopping all elements\n");
	while (stack_size(&stack) > 0) {
		if (stack_pop(&stack, (void **)&data) == 0)
			free(data);
	}
	if ((data = stack_peek(&stack)) != NULL)
		fprintf(stdout, "\nPeeking at the top element [value]=%g\n", *data);
	else
		fprintf(stdout, "\nPeeking at the top element [value]=NULL\n");
	print_stack(&stack);

	fprintf(stdout, "\nDestroying the stack\n");
	stack_destroy(&stack);
	return 0;
}