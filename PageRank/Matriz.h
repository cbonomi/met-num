#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

class Matriz {

private:
    int** mt;

public:
    int sizeColumna, sizeFila;
    Matriz(int vn, int vm);

    void set(int i, int j, int valor);
    int get(int i, int j);
    ~Matriz();

};

#endif
