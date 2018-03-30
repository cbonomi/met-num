#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

class Matriz {

private:
    float** mt;
    int cantidadDeDigitosMaxima(Matriz &M);


public:
    int sizeColumna, sizeFila;

    Matriz(int n, int m);

    Matriz operator+(Matriz &B);
    Matriz operator*(Matriz &B);
    void operator*(float valor);
    //float operator[][](const int &i, const int &j);

    void set(const int i, const int j, const float valor);
    float get(const int i, const int j);
    ~Matriz();

};
std::ostream& operator << (std::ostream &o, Matriz &B);

#endif
