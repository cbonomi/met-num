#include "VectorMapMatrix.h"
#include <sstream>

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
VectorMapMatrix VectorMapMatrix::operator+(VectorMapMatrix const &B) {
    if(cantFilas() == B.cantFilas() and cantColumnas() == B.cantColumnas()) {
        VectorMapMatrix result(cantFilas(), cantColumnas());
        map<uint, float>::const_iterator it1 = m[0].begin();
        map<uint, float>::const_iterator it2 = B.m[0].begin();
        uint f = 0;
        while (f < cantFilas()) {
            while(it1 != m[f].end() or it2 != B.m[f].end()) {
                if (it2 == B.m[f].end() or it1->first < it2->first){
                    result.asignar(f, it1->first, it1->second); // B tiene un valor nulo, solo coloco el valor de A.
                    it1++;
                } else if (it1 == m[f].end() or it1->first > it2->first) {
                    result.asignar(f, it2->first, it2->second); // A tiene un valor nulo, solo coloco el valor de B.
                    it2++;
                } else {
                    result.asignar(f, it1->first, it1->second + it2->second); //Ambas matrices tienen valores no nulos.
                    it1++;
                    it2++;
                }
            }
            f++; //voy a la siguiente fila
            it1 = m[f].begin(); //acomodo los iteradores para la nueva fila.
            it2 = B.m[f].begin();
        }
        return result;
    } else {
        VectorMapMatrix result; //no se puede operar, devuelvo matriz 0x0.
        return result;
    }
}

VectorMapMatrix VectorMapMatrix::operator*(const VectorMapMatrix &B) {
    if(cantColumnas() == B.cantFilas()) {
        VectorMapMatrix result(cantFilas(), B.cantColumnas());
        vector<vector<float> > sumasParciales(cantColumnas(),vector<float>(B.cantColumnas(), 0));
        uint f = 0; //Recorro sobre A, y cuando estoy en el elemento a(ij) multiplico por la fila j de B, sumándolo en result.
        while(f < cantFilas()) {
            map<uint, float>::const_iterator it1 = m[f].begin();
            while (it1 != m[f].end()) {
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

void VectorMapMatrix::operator*(float valor) {
    float acum = 0;
    for (int i = 0; i<cantFilas(); i++) {
        for (int j = 0; j<cantColumnas(); j++) {
            acum = at(i, j) * valor;
            asignar(i, j, acum);
        }
    }
}

VectorMapMatrix VectorMapMatrix::triangularMatriz() {}


/*
 * Funciones para mostrar la matriz
 */

string convertirAString(float num) {
    stringstream ss (stringstream::in | stringstream::out);
    ss << num;
    string cadena = ss.str();
    return cadena;
}

int cantidadDeDigitosMaxima(VectorMapMatrix &M) {
    int maximo = 0;
    int cantDigitos = 0;
    for (int i=0; i < M.cantFilas(); i++) {
        for (int j=0; j< M.cantColumnas(); j++) {
            cantDigitos = convertirAString(M.at(i,j)).length();
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

std::ostream& operator << (std::ostream &o, VectorMapMatrix &B) {
    string espacio;
    int cantDigitos = cantidadDeDigitosMaxima(B);
    for (int i=0; i < cantDigitos; i++) {
        espacio += " ";
    }

    for (int i = 0; i < B.cantFilas(); i++) {
        for (int j = 0; j < B.cantColumnas(); j++) {
            if (B.at(i, j) < 0)
                espacio = " \t";
            else
                espacio = " \t \t \t";
            o << agregarEspacios(B.at(i, j), cantDigitos);
        }
        o << "\n";
    }
    return o;
}