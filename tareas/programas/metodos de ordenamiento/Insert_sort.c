#include <stdio.h>
#include <stdlib.h>

/*
 print int array
*/
static void print_arr(int *arr, int lenght) {
    int i;
    
    if(arr == NULL)
        return;
    
    for(i = 0; i < lenght; i++)
        fprintf(stdout, "%04d ", arr[i]);
    
    fprintf(stdout, "\n");
    return;
}

/*
    insert sort
*/
static void insert_sort(int *arr, int lenght) {
    int i, j, aux;
    // Not allow NULL pointer
    if(arr == NULL)
        return;
    
    for(i = 1; i < lenght; i++) {
        for(j = i; j > 0; j--) {
            if(arr[j] < arr[j-1]) {
                aux = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = aux;
            }
        }
        print_arr(arr, i+1);
    }
    return;
}

int main(int argc, const char *argv[]) {
    int *arr, i;
    // Not allow empty set of arguments
    if(argc <= 1) {
        fprintf(stdout, "No arguments were provided\n");
        return 0;
    }
    // Set memory space for int array
    if((arr = (int *)malloc(sizeof(int) * (argc -1))) == NULL)
        return 1;
    // Filling the array with arguments
    for(i = 0; i < argc - 1; i++)
        arr[i] = atoi(argv[i+1]);
    // Printing array
    fprintf(stdout, "\nProvided array: \n");
    print_arr(arr, argc - 1);
    // Sorting array
    fprintf(stdout, "\nSorting array: \n");
    insert_sort(arr, argc - 1);
    // Printing array
    fprintf(stdout, "\nSorted array: \n");
    print_arr(arr, argc - 1);
    
    printf("\n");
    free(arr);
    return 0;
}
