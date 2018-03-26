#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Matriz.h"

using namespace std;

Matriz::Matriz(int vm, int vn) {
    m = vm;
    n = vn;

    mt = new int*[n];

    for (int i=0; i<n; i++) {
        mt[i] = new int[m];
    }
}

Matriz::~Matriz(){
    for(int i=0; i<n; i++) {
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

