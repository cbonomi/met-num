#include "MapMatrix.h"

MapMatrix::MapMatrix() {
    width = 0;
    height = 0;
}

MapMatrix::MapMatrix(uint h, uint w) {
    height = h;
    width = w;
}

float& MapMatrix::operator[](const pair<uint, uint> &p) {
    return m[p];
}

MapMatrix MapMatrix::sumaMatrices(const MapMatrix &A, const MapMatrix &B) {
    if(A.width == B.width and A.height == B.height) {
        MapMatrix result(A.height, A.width);
        map::iterator it1 = A.m.begin();
        map::iterator it2 = B.m.begin();
        while(it1 != A.m.end() or it2 != B.m.end()) {
            if (it2 == B.m.end() or it1->first < it2->first){
                result[it1->first] = it1->second; // B tiene un valor nulo, solo coloco el valor de A.
            } else if (it1 == A.m.end() or it1->first > it2->first) {
                result[it2->first] = it2->second; // A tiene un valor nulo, solo coloco el valor de B.
            } else {
                result[it1->first] = it1->second + it2->second; //Ambas matrices tienen valores no nulos.
            }
        }
    } else {
        MapMatrix result; //no se puede operar
        return result;
    }
}