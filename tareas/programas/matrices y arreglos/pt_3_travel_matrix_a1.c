
#include <stdio.h>
#include <stdlib.h>

void imprimirMatriz(int m[6][4]){
    int i,j;

    for(i=0; i<6; i++){
        for(j=0; j<4; j++){
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
    int matriz[6][4];
    int i, j, contador=1;

    for(i=0; i<6; i++){
        for(j=0; j<4; j++){
            matriz[i][j]=0;
        }
    }

    printf("Matriz inicial: \n");
    imprimirMatriz(matriz);

	for(i=0; i<6; i++){
		for(j=0; j<4; j++){
			if(i%2){
				matriz[i][3-j]=contador;
			}
			else{
				matriz[i][j]=contador;
			}
			contador++;
		}
	}

    printf("\nMatriz con recorrido: \n");
    imprimirMatriz(matriz);
    
    return 0;
}
