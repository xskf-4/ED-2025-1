
#include <stdio.h>
#include <stdlib.h>

void imprimirMatriz(int m[6][6]){
    int i,j;

    for(i=0; i<6; i++){
        for(j=0; j<6; j++){
        	if(m[i][j]>9){
        		printf("%d ", m[i][j]);
			}
			else{
				printf(" %d ", m[i][j]);
			}
        }
        printf("\n");
    }
	
	printf("\n");
	system("pause");
	printf("\n\n");
}

int main(){
    int matriz[6][6];
    int i, j, contador=1;

    for(i=0; i<6; i++){
        for(j=0; j<6; j++){
            matriz[i][j]=0;
        }
    }

    printf("Matriz inicial: \n");
    imprimirMatriz(matriz);
	
    i=5;
    j=5;

    do{
        
		if(i==0 || i==5){
            matriz[i][j]=contador;
            j--;
        }
        
        if(j==-1 && i==5){
            i=4;
            j=1;
            contador++;
        }
        
        if(i>0 && i<5){
            matriz[i][j]=contador;
            i--;
            j++;
        }
        
        contador++;
    }while(i!=-1 && j!=-1);

    printf("\nMatriz con recorrido: \n");
    imprimirMatriz(matriz);
    
    return 0;
}
