#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "list.h"

/*
    Imprimir lista
*/

static void print_list (const List *list) {
    ListNode *node;
    int i;
    char *data;

    fprintf(stdout, "Longitud de la lista: %d\n", list_size(list));

    i = 0;
    node = list_head(list);

    while (1) {
        data = list_data(node);
        fprintf(stdout, "list.node[%03d]=%c, %p -> %p \n", i, *data, node, node->next);

        i++;

        if (list_is_tail(node))
            break;
        else
            node = list_next(node);
    }

   return;
}


int main (int argc, char **argv) {
    List list;
    ListNode *node;
    // Determinar una semilla para numeros pseudoaleatorios
    srand(time(NULL));

    int i, j, r_num;
    char *data, arr_char[]={'A','W', 'T', 'M'};

    // Inicializar la lista
    list_init(&list, free);

    // Llenar la lista
    node = list_head(&list);
    for (i = 0; i < 10; i++) {

        if ((data = (char *)malloc(sizeof(char))) == NULL)
            return 1;
        // Seleccion aleatoria de numero entre 65 y 90 correspondientes al rango A-Z
        r_num=rand()%25+65;
        *data = (char)r_num;

        if (list_ins_next(&list, NULL, data) != 0)
            return 1;
    }

    print_list(&list);

    //Insertar nodos con data A, W, T, M de forma aleatoria
    for(j=0; j<4; ++j){
        node = list_head(&list);
        r_num=rand()%list_size(&list);//Determinar la posicion del nodo a insertar
        
        for (i = 1; i < r_num; ++i)
            node = list_next(node);
        
        if ((data = (char *)malloc(sizeof(char))) == NULL)
            return 1;

        *data = arr_char[j];

        fprintf(stdout, "\nInsertando un nodo en la posicion #%03d con data \'%c\'\n", r_num, *data);

        if(r_num==0){
            if (list_ins_next(&list, NULL, data) != 0)
                return 1;
        }
        else{
            if (list_ins_next(&list, node, data) != 0)
                return 1;
        }

        print_list(&list);
    }

    // Eliminar un nodo de forma aleatoria cuatro veces
    for(j=0; j<4; ++j){
        node = list_head(&list);
        r_num=rand()%list_size(&list);//Determinar el numero del nodo a eliminar

        for (i = 1; i < r_num; ++i)
            node = list_next(node);

        fprintf(stdout, "\nEliminando el nodo #%03d\n", r_num);

        data = list_data(node);

        if(r_num==0){
            if (list_rem_next(&list, NULL, (void**)&data) != 0)
            return 1;
        }
        else{
            if (list_rem_next(&list, node, (void**)&data) != 0)
            return 1;
        }

        print_list(&list);
    }

    // Destruir la lista
    fprintf(stdout, "\nLista destruida\n");
    list_destroy(&list);

    return 0;
}
