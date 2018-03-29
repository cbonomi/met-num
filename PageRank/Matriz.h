#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

class Matriz {

private:
    float** mt;

public:
    int sizeColumna, sizeFila;

    Matriz(int n, int m);

    Matriz operator+(Matriz &B);
    Matriz operator*(Matriz &B);
    //float operator[][](const int &i, const int &j);

    void set(int i, int j, int valor);
    float get(const int i, const int j);
    ~Matriz();

};
std::ostream& operator << (std::ostream &o, Matriz &B);

#endif
