
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void imprimirArreglo(int *arr, int tam){
    int i;

    printf("\n\n");
    for(i=0; i<tam; i++){
        if(arr[i]>0 && arr[i]<10){
            printf(" %d ", arr[i]);
        }
        else{
            printf("%d ", arr[i]);
        }
    }
    printf("\n\n");
}

int main(int n_arg, char *argv[]){

    int *arreglo;
    int i, pos_x;
    char *n_cuenta;
    
    arreglo=(int *)malloc(sizeof(int)*10);
    n_cuenta=argv[n_arg-1];

    for(i=0; i<10; i++){
        arreglo[i]=2*(i+1);
    }

    imprimirArreglo(arreglo, 10);
    system("pause");

    pos_x=((int)n_cuenta[strlen(n_cuenta)-1]-48)%10;

    if(pos_x<0){
        pos_x=0;
    }

    arreglo[pos_x]=-1;

    imprimirArreglo(arreglo, 10);

    free(arreglo);
    system("pause");
    return 0;
}
