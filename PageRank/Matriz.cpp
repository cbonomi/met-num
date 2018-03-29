#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Matriz.h"

using namespace std;

Matriz::Matriz(int n, int m) {
    sizeColumna = n;
    sizeFila = m;//(i,j) seria fila i y columna j, como siempre

    mt = new float*[sizeFila];

    for (int i=0; i<sizeFila; i++) {
        mt[i] = new float[sizeColumna];
    }
}

Matriz::~Matriz(){
    for(int i=0; i<sizeFila; i++) {
        delete[] mt[i];
    }
    delete[] mt;
}

Matriz Matriz::operator+(Matriz &B) {
    Matriz ret = Matriz(sizeColumna, sizeFila);
    for (int i = 0; i<sizeFila; i++) {
        for (int j = 0; j<sizeColumna; j++) {
            ret.set(i, j, get(i,j) + B.get(i,j));
        }
    }
    return ret;
}

Matriz Matriz::operator*(Matriz &B) {
    Matriz ret = Matriz(sizeColumna, sizeFila);
    int acum = 0;
    for (int i = 0; i<sizeFila; i++) {
        for (int j = 0; j<sizeColumna; j++) {
            for (int k = 0; k<sizeFila; k++) {
                acum += get(i,k) * B.get(k,j);
            }
            ret.set(i, j, acum);
            acum = 0;
        }
    }
    return ret;
}

std::ostream& operator << (std::ostream &o, Matriz &B) {
    for (int i = 0; i < B.sizeFila; i++) {
        for (int j = 0; j < B.sizeColumna; j++) {
            o << B.get(i, j) << " \t ";
        }
        o << "\n";
    }
    return o;
}

void Matriz::set(int i, int j, int valor) {
    *(*(mt+i)+j) = valor;
}

float Matriz::get(const int i, const int j) {
    return *(*(mt+i)+j);
}

