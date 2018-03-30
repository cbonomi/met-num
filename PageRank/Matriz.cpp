#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Matriz.h"
#include <sstream>

using namespace std;

Matriz::Matriz(int n, int m) {
    sizeFila = n;//(i,j) seria fila i y columna j, como siempre
    sizeColumna = m;

    mt = new float*[sizeFila];

    for (int i=0; i<sizeFila; i++) {
        float* vect = new float[sizeColumna];
        for (int j=0; j<sizeColumna; j++)
            vect[j] = 0;
        mt[i] = vect;
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
    Matriz ret = Matriz(sizeFila, B.sizeColumna);
    float acum = 0;
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

void Matriz::operator*(float valor) {
    float acum = 0;
    for (int i = 0; i<sizeFila; i++) {
        for (int j = 0; j<sizeColumna; j++) {
            acum = get(i, j) * valor;
            set(i, j, acum);
        }
    }
    cout << *this;
}

string convertirAString(float num) {
    stringstream ss (stringstream::in | stringstream::out);
    ss << num;
    string cadena = ss.str();
    return cadena;
}

int cantidadDeDigitosMaxima(Matriz &M) {
    int maximo = 0;
    int cantDigitos = 0;
    for (int i=0; i < M.sizeFila; i++) {
        for (int j=0; j< M.sizeColumna; j++) {
            cantDigitos = convertirAString(M.get(i,j)).length();
            if (maximo < cantDigitos)
                maximo = cantDigitos;
        }
    }
    return maximo;
}

string agregarEspacios(float valor, int cantidadMaxima) {
    string ret = convertirAString(valor);
    cantidadMaxima = cantidadMaxima - ret.length();
    for (int i=0; i < cantidadMaxima+1; i++) {
        ret = " " + ret;
    }
    return ret;
}

std::ostream& operator << (std::ostream &o, Matriz &B) {
    string espacio;
    int cantDigitos = cantidadDeDigitosMaxima(B);
    for (int i=0; i < cantDigitos; i++) {
        espacio += " ";
    }

    for (int i = 0; i < B.sizeFila; i++) {
        for (int j = 0; j < B.sizeColumna; j++) {
            if (B.get(i, j) < 0)
                espacio = " \t";
            else
                espacio = " \t \t \t";
            o << agregarEspacios(B.get(i, j), cantDigitos);
        }
        o << "\n";
    }
    return o;
}

void Matriz::set(const int i, const int j, const float valor) {
    *(*(mt+i)+j) = valor;
}

float Matriz::get(const int i, const int j) {
    return *(*(mt+i)+j);
}

