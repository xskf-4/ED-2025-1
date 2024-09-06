
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rellenarMatriz(int **matriz, int n_filas, char *cad_columnas){
    int i, j, n_columnas;
    for(i=0; i<n_filas; i++){
        n_columnas=(int)cad_columnas[i]-48;
        for(j=0; j<n_columnas; j++){
            matriz[i][j]=n_columnas;
        }
    }
}

void imprimirMatriz(int **matriz, int n_filas, char *cad_columnas){
    int i, j, n_columnas;
    printf("\n\n");
    for(i=0; i<n_filas; i++){
        n_columnas=(int)cad_columnas[i]-48;
        printf("[%d]: ", n_columnas);
        for(j=0; j<n_columnas; j++){
            printf("%d[%p]   ", matriz[i][j], &matriz[i][j]);
        }
        if(matriz[i]==NULL){
            printf("NULL");
        }
        printf("\n");
    }
    printf("\n\n");
}

int main(int n_arg, char *argv[]){

    int n_filas=strlen(argv[1]), n_columnas, i;
    int **matriz=(int **)malloc(n_filas * sizeof(int *));
    char *aux_cad=argv[1];
    //inicializacion de la matriz
    for(i=0; i<n_filas; i++){
        n_columnas=(int)aux_cad[i]-48;
        if(n_columnas>0){
            matriz[i]=(int *)malloc(n_columnas * sizeof(int));
        }
        else{
            matriz[i]=NULL;
        }
    }

    rellenarMatriz(matriz, n_filas, aux_cad);

    imprimirMatriz(matriz, n_filas, aux_cad);

    free(matriz);
    system("pause");
    return 0;
}
