#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Canales {

    char nombre[20];
    float rating;
    char tipoCanal[20];
};

typedef struct Canales *canalesPtr;

canalesPtr crearVector(int t);

canalesPtr cargarNulos();

void cargarCanalesNulos(canalesPtr c[], int t);

void leerArchivo(canalesPtr c[]);

void mostrarCanales(canalesPtr c[], int t);

void eliminarCanales(canalesPtr c[], int t);

void guardarDatos(canalesPtr c[], int t);

int main()
{
    int tam = 5;
    canalesPtr c = crearVector(tam);

    cargarCanalesNulos(c, tam);

    leerArchivo(c);

    mostrarCanales(c, tam);

    eliminarCanales(c, tam);

    guardarDatos(c, tam);

    return 0;
}

canalesPtr crearVector(int t){

    canalesPtr c = malloc(t*sizeof(struct Canales));
    return c;
};

canalesPtr cargarNulos(){

    canalesPtr c = malloc(sizeof(struct Canales));

    strcpy(c->nombre, "VACIO");
    c->rating = -1;
    strcpy(c->tipoCanal, "VACIO");

    return c;
};

void cargarCanalesNulos(canalesPtr c[], int t){

    for( int i=0; i<t; i++){

        c[i] = cargarNulos();
    }
};

void leerArchivo(canalesPtr c[]){

    FILE * archivo = fopen("canales.txt", "r");

    if ( archivo == NULL){

        printf("No se puede abrir");
        exit(1);
    }

    int pos = 0;

    while ( !feof (archivo)){

        fscanf(archivo, "%[a-zA-Z], %f, %[a-zA-Z]\n", c[pos]->nombre, &c[pos]->rating, c[pos]->tipoCanal);

        pos ++;
    }

    fclose(archivo);
};

void mostrarCanales(canalesPtr c[], int t){

    for(int i=0; i<t; i++){
        if(c[i]->rating != -1){

            printf("----------------\n");
            printf("Nombre: %s\n", c[i]->nombre);
            printf("Rating: %.2f\n", c[i]->rating);
            printf("Tipo: %s\n", c[i]->tipoCanal);
        }
    }
};

void eliminarCanales(canalesPtr c[], int t){

    for(int i=0; i<t; i++){

        if(c[i]->rating < 5){

            c[i] = cargarNulos();
        }
    }
};

void guardarDatos(canalesPtr c[], int t){

    FILE *archivo = fopen("eliminados.txt", "w");

    for(int i=0; i<t; i++){
        if(c[i]->rating != -1){

            fprintf(archivo, "%s %f %s", c[i]->nombre, c[i]->rating, c[i]->tipoCanal);
        }
    }

    fclose(archivo);
};
