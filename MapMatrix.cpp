#include "MapMatrix.h"

MapMatrix::MapMatrix() {
    width = 0;
    height = 0;
}

MapMatrix::MapMatrix(uint h, uint w) {
    height = h;
    width = w;
}

uint MapMatrix::cantFilas() const {
    return height;
}

uint MapMatrix::cantColumnas() const {
    return width;
}

void MapMatrix::asignar(const pair<uint, uint> p, const float value) {
    if (value==0) {
        asignar0(p);
    } else if (p.first < height and p.second<width) {
        m[p] = value;
    }
}

const float MapMatrix::at(const pair<uint, uint> p) const {
    float result;
    if(m.count(p) == 0) {
        result = 0;
    } else {
        result = m.at(p);
    }
    return result;
}

float& MapMatrix::operator[](const pair<uint, uint> &p) {
    if (p.first < height and p.second < width) {
        return m[p];
    }
}

void MapMatrix::asignar0(const pair<uint, uint> p) {
    m.erase(p);
}

MapMatrix MapMatrix::sumaMatrices(const MapMatrix &A, const MapMatrix &B) {
    if(A.width == B.width and A.height == B.height) {
        MapMatrix result(A.height, A.width);
        map<pair<uint, uint>, float>::const_iterator it1 = A.m.begin();
        map<pair<uint, uint>, float>::const_iterator it2 = B.m.begin();
        while(it1 != A.m.end() or it2 != B.m.end()) {
            if (it2 == B.m.end() or it1->first < it2->first){
                result.asignar(it1->first, it1->second); // B tiene un valor nulo, solo coloco el valor de A.
                it1++;
            } else if (it1 == A.m.end() or it1->first > it2->first) {
                result.asignar(it2->first, it2->second); // A tiene un valor nulo, solo coloco el valor de B.
                it2++;
            } else {
                result.asignar(it1->first, it1->second + it2->second); //Ambas matrices tienen valores no nulos.
                it1++;
                it2++;
            }
        }
    } else {
        MapMatrix result; //no se puede operar, devuelvo matriz 0.
        return result;
    }
}

MapMatrix MapMatrix::productoMatrices(const MapMatrix &A, const MapMatrix &B) {
    if(A.width == B.height) {
        MapMatrix result(A.height, B.width);
        uint f = 0;
        uint c = 0;
        while(f < result.height) {
            while (c < result.width) {
                for(int k=0; k < A.width; k++) {
                    result.asignar(make_pair(f,c), result.at(make_pair(f,c)) + A.at(make_pair(f,k)) * B.at(make_pair(k,c)));
                }
                c++;
            }
            f++;
        }
    }
}

MapMatrix MapMatrix::triangularMatriz() {}