#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 print int array
*/
static void print_arr(int *arr, int lenght) {
    int i;
    // Not allow NULL pointer
    if(arr == NULL)
        return;
    
    for(i = 0; i < lenght; i++)
        fprintf(stdout, "%04d ", arr[i]);
    
    fprintf(stdout, "\n");
    return;
}

/*
    counting sort
*/
void counting_sort(int *arr, int lenght) {
    int i, max_arr, min_arr, *aux_arr, aux_lenght, increment, *sorted_arr;
    // Not allow NULL pointer
    if(arr == NULL)
        return;
    // Setting max and min elements in array
    max_arr = arr[0];
    min_arr = arr[0];
    for(i = 1; i < lenght; i++) {
        if(max_arr < arr[i])
            max_arr = arr[i];
        if(min_arr > arr[i])
            min_arr = arr[i];
    }
    // Initializing auxiliar array
    aux_lenght = max_arr - min_arr + 1;
    aux_arr = (int *)malloc(sizeof(int) * (aux_lenght));
    memset(aux_arr, 0, aux_lenght);
    // Starting to counting
    for(i = 0; i < lenght; i++) {
        aux_arr[arr[i]-min_arr] += 1;
    }
    print_arr(aux_arr, aux_lenght);
    // Filling the hole array and increment
    increment = 0;
    for(i = 0; i < aux_lenght; i++) {
        increment += aux_arr[i];
        aux_arr[i] = increment;
    }
    print_arr(aux_arr, aux_lenght);
    // Initializing sorted array
    sorted_arr = (int *)malloc(sizeof(int) * lenght);
    //Filling sorted array
    for(i = 0; i < lenght; i++) {
        sorted_arr[aux_arr[arr[i] - min_arr] - 1] = arr[i];
        aux_arr[arr[i] - min_arr] --;
    }
    // Copying sorted array to original array
    for(i = 0; i < lenght; i++)
        arr[i] = sorted_arr[i];
    
    free(sorted_arr);
    free(aux_arr);
    return;
}

int main(int argc, char **argv) {
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
    // Printing provided array
    fprintf(stdout, "\nProvided array: \n");
    print_arr(arr, argc - 1);
    // Sorting array
    fprintf(stdout, "\nSorting array: \n");
    counting_sort(arr, argc - 1);
    // Printing sorted array
    fprintf(stdout, "\nSorted array: \n");
    print_arr(arr, argc - 1);

    fprintf(stdout, "\n");
    free(arr);
    return 0;
}