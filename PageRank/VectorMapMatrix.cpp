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
	return m[0][0];//agregue esto solo para devolver algo en caso de que se invoque mal
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
    for (unsigned int i = 0; i<cantFilas(); i++) {
        for (unsigned int j = 0; j<cantColumnas(); j++) {
            acum = at(i, j) * valor;
            asignar(i, j, acum);
        }
    }
}

VectorMapMatrix VectorMapMatrix::triangularMatriz() {}

void VectorMapMatrix::permutar(VectorMapMatrix m, unsigned int j, unsigned int i){
	VectorMapMatrix p = VectorMapMatrix(m.cantFilas(),m.width);
	for (unsigned int k = 0; i<m.cantFilas(); i++){ //genero la matriz de permutacion
		if (k!=i && k!=j){
			p.asignar(k, k, 1);
		} else if (k==i){
			p.asignar(j, k, 1);
		} else {
			p.asignar(i, k, 1);
		}
	}
	m = p*m; //multiplico las matrices, p va a la izquierda porque quiero permutar filas



}

pair<vector<float>,short> VectorMapMatrix::EG(VectorMapMatrix m, vector<float> b) {
	unsigned int i,j;
	vector<float> res;
	short status = 0; //status default, el sistema tiene una unica solucion posible
	float A_kk, A_jk;
	VectorMapMatrix copy = VectorMapMatrix(m);
	VectorMapMatrix Mk = VectorMapMatrix(m.cantFilas(),m.width);
	bool cont = false; //el bool da es false si en toda la columna de i en adelante es 0, es decir me tengo que saltear este paso
	for(i = 0; i < copy.cantFilas()-1; i++){ //itero sobre las filas, excepto la ultima porque ahi no tengo que hacer nada
		for(j = i; i < copy.cantFilas(); i++){ //itero sobre las filas desde i en adelante, estaria por fijarme si tengo que hacer o no calculo en el paso i de la EG
			if(copy.at(j,i) != 0){ //si no hay un 0 en la posicion j,i
				cont = true;
				if(copy.at(i,i) == 0){
					permutar(copy,j,i); //cambio de lugar las filas porque habia un 0 en la diagonal pero no en el resto de la columna
				}
				break;
			}
			
		}
		A_kk = copy.at(j,i);
		for(j = i + 1; i < copy.cantFilas(); i++){ //cálculo del paso i si corresponde
			if (!cont){break;} //si me tengo que saltear este paso no calculo nada
			if(copy.at(j,i) != 0){A_jk = copy.at(j,i);} //A_jk y A_kk son los valores que determinan a las matrices Mk que uso para llegar desde A a U, sabiendo que PA = LU
			else{A_jk = 0.0;}
			Mk.asignar(j,i,(-1.0)*A_jk/A_kk);
			b[j] = b[j]-A_jk/A_kk*b[i]; //no me olvido de actualizar el vector b
		}
		if(cont){
			copy = Mk*copy;
			cont = false;
		}
		
	}
	for(i = copy.cantFilas(); i == 0; i--){
		j = i-1; //porque i arranca en copy.cantFilas() pero se indexa desde 0 a copy.cantFilas() -1
		if(copy.at(j,j) == 0 && b[j] != 0){
			status = -1; //el sistema es incompatible
			break;
		}
		if(copy.at(j,j) == 0 && b[j] == 0){
			status = 1; //hay infinitos resultados
			res[j] = 0;
		}
		else{
			res[j] = b[j]/copy.at(j,j); //tengo A_jj*x_j = b_j, paso dividiendo el A_jj
			if (j!=0){
				b[j-1] = b[j-1] - res[j]*copy.at(j-1,j); //esto es importante, al b_j-1 le paso restando el A_j-1j*x_j, porque ya conozco el resultado de X_j, de forma que en la siguiente iteracion solo voy a tener algo de esta pinta A_jj*x_j = b_j
			}
		}
	}
	return pair<vector<float>,short>(res,status);
}
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
    for (unsigned int i=0; i < M.cantFilas(); i++) {
        for (unsigned int j=0; j< M.cantColumnas(); j++) {
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

    for (unsigned int i = 0; i < B.cantFilas(); i++) {
        for (unsigned int j = 0; j < B.cantColumnas(); j++) {
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
