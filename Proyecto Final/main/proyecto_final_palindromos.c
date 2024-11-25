
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "list.h"

/*
    data struct for lists
*/
typedef struct {
    char *string;
    int row;
    int column;
} DataStruct;

/*
    is palindrome function
*/
static int is_palindrome(char *string_x) {
    int i, string_length;
    char *aux_string;
    // If string_x is NULL return 0;
    if(string_x == NULL)
        return 0;
    
    aux_string = (char *)malloc(sizeof(char) * strlen(string_x));
    strcpy(aux_string, string_x);
    string_length = strlen(aux_string);
    // Lowering all characters from string
    for(i = 0; i < string_length; i++)
        aux_string[i] = tolower((unsigned char)aux_string[i]);

    // Comparing the caracters
    for(i = 0; i < string_length/2; i++)
        if(aux_string[i] != aux_string[string_length - (i + 1)])
            return 0;
            
    free(aux_string);
    return 1;
}

/*
    print List
*/
static void print_list(List *list, char *list_title, int max_len) {
    int i, j;
    ListNode *node;
    DataStruct *data_struct;

    node = list_head(list);
    i = 0;

    fprintf(stdout, "\nPrinting: %s | size : %d\n", list_title, list_size(list));
    if(list_size(list) > 0) {
        while(node != NULL){
            data_struct = (DataStruct *)node->data;
            fprintf(stdout, "list[%03d] = %-*s | %03d | %03d |", i, max_len, data_struct->string, data_struct->column, data_struct->row);
            fprintf(stdout, " node allocation: %-14p -> %-14p | data allocation: %p\n", node, list_next(node), list_data(node));
            node = list_next(node);
            i++;
        }
    } else {
        fprintf(stdout, "Empty list\n");
    }

    return;
}

/*
    free data node
*/
void destroy_data_node(void *data) {
    if(data == NULL)
        return;
    
    DataStruct *data_struct;
    data_struct = (DataStruct *)data;

    memset(data_struct->string, 0, strlen(data_struct->string));
    data_struct->column = 0;
    data_struct->row = 0;
    memset(data_struct, 0, sizeof(DataStruct));
    free(data_struct->string);
    free(data_struct);
    return;
}

int main(int argc, char **argv) {
    // File variable
    FILE *file;
    // Auxiliar char pointer
    char string_aux[100];
    // Auxiliar variables
    int i, j, len, max_len;
    char c_aux[3] = {'\0', '\0', '\0'};
    DataStruct *data_struct;
    // List variables
    List words, palindromes;
    ListNode *node;

    fprintf(stdout, "\nStart of program\n\n");

    file = fopen(argv[1], "r");
    // If file cannot be opened return 1
    if(file == NULL){
        fprintf(stdout, "Error opening the file");
        return 1;
    }

    // Initializing words list
    list_init(&words, destroy_data_node);

    i = 0;
    j = 0;
    len = 0;
    max_len = 0;
    memset(string_aux, 0, 100);

    /*
        Loop for filling the words list
    */
    fprintf(stdout, "Starting word list loop\n");
    // while reading a character != END OF FILE
    while(fscanf(file, "%c", &c_aux[1]) != EOF) {
        // Saving '\n' character for last conditional
        if(c_aux[1] == '\n') 
            c_aux[2] = c_aux[1];
        // If read character == '\n', '\t', '\f' '\v', take as ' '
        if(c_aux[1] == '\t' || c_aux[1] == '\n' || c_aux[1] == '\f' || c_aux[1] == '\v' || c_aux[1] == '\r')
            c_aux[1] = ' ';
        // If read character != ' ', add to auxiliar string
        if(c_aux[1] != ' ') {
            string_aux[len] = c_aux[1];
            len++;
        // If lenght > 0 && character behind != ' ', add data_struct(string, # row, # column) to list
        } else if(len > 0 && c_aux[0] != ' ') { 
            string_aux[len] = '\0';
            if((data_struct = (DataStruct *)malloc(sizeof(DataStruct))) == NULL)
                return 1;

            if((data_struct->string = (char *)malloc(sizeof(char ) * (len + 1))) == NULL)
                return 1;

            strcpy(data_struct->string, string_aux);
            data_struct->row = i;
            data_struct->column = j;

            if(list_ins_next(&words, list_tail(&words), data_struct) != 0)
                return 1;

            if(len > max_len)
                max_len = len;

            memset(string_aux, 0, 100);
            len = 0;
            i++;
        }
        // If read character == '\n', # columns increments
        if(c_aux[2] == '\n') {
            j++;
            i = 0;
            c_aux[2] = '\0';
        }
        // Change the character behind
        c_aux[0] = c_aux[1];
    }

    // Print words list info
    print_list(&words, "words list", max_len);

    // Initializing palindromes list
    list_init(&palindromes, NULL);

    /*
        Loop for filling palindromes list
    */
   node = list_head(&words);
   fprintf(stdout, "\n\nStarting palindromes list loop\n");
    while(node != NULL) {
        data_struct = (DataStruct *)list_data(node);
        if(is_palindrome(data_struct->string))
            if((list_ins_next(&palindromes, list_tail(&palindromes), data_struct)) != 0)
                return 1;

        node = list_next(node);
    }

    // Printing palindromes list info
    print_list(&palindromes, "palindromes list", max_len);

    // Destroying lists
    fprintf(stdout, "\n\nDestroying words list\n");
    list_destroy(&words);
    fprintf(stdout, "\nDestroying palindromes list\n");
    list_destroy(&palindromes);
    // End of program
    fprintf(stdout, "\nEnd of program\n");
    return 0;
}