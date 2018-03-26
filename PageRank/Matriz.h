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
    int m, n;
    Matriz(int m, int n);

    void set(int i, int j, int valor);
    int get(int i, int j);

    ~Matriz();

};

#endif