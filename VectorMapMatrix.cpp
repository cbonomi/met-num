#include "VectorMapMatrix.h"

VectorMapMatrix::VectorMapMatrix() {
    width = 0;
}

VectorMapMatrix::VectorMapMatrix(uint h, uint w) : m(h, map<uint,float>()) , width(w) {}

size_t VectorMapMatrix::cantFilas() const {
    return m.size();
}

size_t VectorMapMatrix::cantColumnas() const {
    return width;
}

void VectorMapMatrix::asignar(uint f, uint c, const float value) {
    if (value==0) {
        m[f].erase(c);
    } else if (f < m.size() and c < width) {
        m[f][c] = value;
    }
}

const float VectorMapMatrix::at(uint f, uint c) const {
    float result;
    if(m[f].count(c) == 0) {
        result = 0;
    } else {
        result = m[f].at(c);
    }
    return result;
}

float& VectorMapMatrix::operator[](pair<uint, uint> p) {
    if (p.first < m.size() and p.second < width) {
        return m[p.first][p.second];
    }
}

VectorMapMatrix VectorMapMatrix::sumaMatrices(const VectorMapMatrix &A, const VectorMapMatrix &B) {
    if(A.cantFilas() == B.cantFilas() and A.cantColumnas() == B.cantColumnas()) {
        VectorMapMatrix result(A.cantFilas(), A.cantColumnas());
        map<uint, float>::const_iterator it1 = A.m[0].begin();
        map<uint, float>::const_iterator it2 = B.m[0].begin();
        uint f = 0;
        while (f < A.cantFilas()) {
            while(it1 != A.m[f].end() or it2 != B.m[f].end()) {
                if (it2 == B.m[f].end() or it1->first < it2->first){
                    result.asignar(f, it1->first, it1->second); // B tiene un valor nulo, solo coloco el valor de A.
                    it1++;
                } else if (it1 == A.m[f].end() or it1->first > it2->first) {
                    result.asignar(f, it2->first, it2->second); // A tiene un valor nulo, solo coloco el valor de B.
                    it2++;
                } else {
                    result.asignar(f, it1->first, it1->second + it2->second); //Ambas matrices tienen valores no nulos.
                    it1++;
                    it2++;
                }
            }
            f++; //voy a la siguiente fila
            it1 = A.m[f].begin(); //acomodo los iteradores para la nueva fila.
            it2 = B.m[f].begin();
        }
        return result;
    } else {
        VectorMapMatrix result; //no se puede operar, devuelvo matriz 0x0.
        return result;
    }
}

VectorMapMatrix VectorMapMatrix::productoMatrices(const VectorMapMatrix &A, const VectorMapMatrix &B) {
    if(A.cantColumnas() == B.cantFilas()) {
        VectorMapMatrix result(A.cantFilas(), B.cantColumnas());
        vector<vector<float> > sumasParciales(A.cantColumnas(),vector<float>(B.cantColumnas(), 0));
        uint f = 0; //Recorro sobre A, y cuando estoy en el elemento a(ij) multiplico por la fila j de B, sumándolo en result.
        while(f < A.cantFilas()) {
            map<uint, float>::const_iterator it1 = A.m[f].begin();
            while (it1 != A.m[f].end()) {
                map<uint, float>::const_iterator it2 = B.m[it1->first].begin(); //Si el it1 esta en columna j, creo it2 en fila j.
                while(it2 != B.m[it1->first].end()) {
                    sumasParciales[f][it2->first] += it1->second * it2->second;//asigno en
                    // la fila f de A, la columna marcada por el iterador it2 de B, en result, lo que había mas el producto.
                    it2++;
                }
                it1++;
            }
            f++;
        }
        f = 0;
        uint c = 0;
        while(f < sumasParciales.size()){
            map<uint, float>::iterator hint_iterator = result.m[f].end();
            while(c < sumasParciales[f].size()){
                result.m[f].insert(hint_iterator,make_pair(c, sumasParciales[f][c])); //como el elemento a insertar debe ir al final,
                // le doy el hint que empiece por alli.
                c++; //cplusplus
            }
            f++;
        }
        return result;
    } else {
        return VectorMapMatrix(); //No existe solución.
    }
}

VectorMapMatrix VectorMapMatrix::triangularMatriz() {}