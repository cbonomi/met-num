#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <stdlib.h>
#include "Matriz.h"

int main(int argc, char * argv[]) {
    std::fstream entrada("prueba.txt", std::ios_base::in);

    int cantidadTotalDePaginas;
    int cantidadTotalDeLinks;


    entrada >> cantidadTotalDePaginas >> cantidadTotalDeLinks;

    printf("cantidad paginas: %i \n", cantidadTotalDePaginas);
    printf(" cantidad links: %i \n", cantidadTotalDeLinks);

    Matriz mtrz(cantidadTotalDePaginas, cantidadTotalDeLinks);

    int i, j;

    while (entrada >> i >> j) {
        printf("i: %i\n", i);
        printf("j: %i\n", j);
        mtrz.set(i, j, 1);
    }

    printf("elemento guardado: %i \n", mtrz.get(12, 1));
    printf("elemento nulo: %i \n", mtrz.get(12, 2));


/*    for(int i=0; i<cantidadTotalDeLinks; i++) {
        entrada >> links[i][0] >> links[i][1];

    }*/
    /*
    while (entrada >> a)
    {
        printf("%i ", a);
    }

*/
    return 0;
}
/*
En la primera lı́nea un entero N , la cantidad total de páginas.
En la segunda lı́nea un entero M , la cantidad total de links.
Luego siguen M lı́neas, cada una con dos enteros i j separados
 por un espacio (1 ≤ i, j ≤ N ), indicando que hay un link de la página i a la página j.
        */