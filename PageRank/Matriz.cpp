#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Matriz.h"

using namespace std;

Matriz::Matriz(int vn, int vm) {
    sizeColumna = vn;
    sizeFila = vm;//(i,j) seria fila i y columna j, como siempre

    mt = new int*[sizeFila];

    for (int i=0; i<sizeFila; i++) {
        mt[i] = new int[sizeColumna];
    }
}

Matriz::~Matriz(){
    for(int i=0; i<sizeFila; i++) {
        delete[] mt[i];
    }
    delete[] mt;
};


void Matriz::set(int i, int j, int valor) {
    *(*(mt+i)+j) = valor;
}

int Matriz::get(int i, int j) {
    return *(*(mt+i)+j);
}
