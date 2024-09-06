
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct alumno{
    char nombre[25];
    int edad;
    int calificacion;
};

typedef struct alumno al;

void imprimirCabecera(){
    int i;
    printf("\n\nNombre");
    for(i=0; i<26-strlen("Nombre"); i++){
        printf(" ");
    }
    printf("Edad   Calificacion");
}

void imprimirAlumno(al alumno_x){
    int i;
    //Impresion del nombre
    printf("\n%s", alumno_x.nombre);
    for(i=0; i<26-strlen(alumno_x.nombre); i++){
        printf(" ");
    }
    //Impresion de la edad
    if(alumno_x.edad>0 && alumno_x.edad<10){
        printf("   %d   ", alumno_x.edad);
    }
    else{
        printf("  %d   ", alumno_x.edad);
    }
    //Impresion de la calificion
    for(i=0; i<10; i++){
        printf(" ");
    }
    if(alumno_x.edad>0 && alumno_x.calificacion<10){
        printf(" %d", alumno_x.calificacion);
    }
    else{
        printf("%d", alumno_x.calificacion);
    }
}

void imprimirTablaNormal(al *alumnos, int n_alumnos){
    int i;
    imprimirCabecera();
    for(i=0; i<n_alumnos; i++){
        imprimirAlumno(alumnos[i]);
    }
}

void imprimirTablaInvertida(al *alumnos, int n_alumnos){
    int i;
    imprimirCabecera();
    for(i=n_alumnos-1; i>=0; i--){
        imprimirAlumno(alumnos[i]);
    }
}

void imprimirEstadisticas(al *alumnos, int n_alumnos){
    int i;
    float prom_edad=0, prom_calificacion=0;

    for(i=0; i<n_alumnos; i++){
        prom_edad+=(float)alumnos[i].edad;
        prom_calificacion+=(float)alumnos[i].calificacion;
    }

    prom_edad/=(float)n_alumnos;
    prom_calificacion/=(float)n_alumnos;

    printf("\n\nEstadisticas: \nPromedio de edad: %g \nPromedio de calificacion: %g", prom_edad, prom_calificacion);
}

int main(int n_arg, char  *argv[]){

    al *alumnos;
    int i, n_alumnos;
    
    n_alumnos=(int)((n_arg-1)/3);
    alumnos=(al *)malloc(sizeof(al)*n_alumnos);
    //Comienza la Asignacion de alimnos
    for(i=0; i<n_alumnos; i++){
        //Se asigna el nombre
        strcpy(alumnos[i].nombre, argv[i*3+1]); //Asignar el nombre al alumno
        //Se asigna la edad
        alumnos[i].edad=atoi(argv[i*3+2]);  //Asignar la edad al alumno
        //Se asigna la calificaion
        alumnos[i].calificacion=atoi(argv[i*3+3]); //Asignar la calificacion al alumno
    }
    //Se imprime la tabla en orden de asignacion
    imprimirTablaNormal(alumnos, n_alumnos);
    //Se imprimen las estadisticas
    imprimirEstadisticas(alumnos, n_alumnos);
    //Se imprime la tabla en orden inverso
    imprimirTablaInvertida(alumnos, n_alumnos);

    printf("\n\n");
    free(alumnos);
    system("pause");
    return 0;
}
