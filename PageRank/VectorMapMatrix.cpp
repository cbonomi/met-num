#include "VectorMapMatrix.h"
#include <math.h>
#include <list>
#include <utility>
#include <sstream>

VectorMapMatrix::VectorMapMatrix() {
    width = 0;
}

VectorMapMatrix::VectorMapMatrix(uint h, uint w) : m(h, map<uint,double>()) , width(w) {}

size_t VectorMapMatrix::cantFilas() const {
    return m.size();
}

size_t VectorMapMatrix::cantColumnas() const {
    return width;
}

void VectorMapMatrix::asignar(uint f, uint c, const double value) {
    if (abs(value) < 0.1) {
        m[f].erase(c);
    } else if (f < m.size() and c < width) {
        m[f][c] = value;
    }
}

const double VectorMapMatrix::at(uint f, uint c) const {
    double result;
    if(m[f].count(c) == 0) {
        result = 0;
    } else {
        result = m[f].at(c);
    }
    return result;
}

double& VectorMapMatrix::operator[](pair<uint, uint> p) {
    if (p.first < m.size() and p.second < width) {
        return m[p.first][p.second];
    }
    return m[0][0];//agregue esto solo para devolver algo en caso de que se invoque mal
}
VectorMapMatrix VectorMapMatrix::operator+(VectorMapMatrix const &B) {
    unsigned int f = 0;
    unsigned int c = 0;
    if(cantFilas() == B.cantFilas() and cantColumnas() == B.cantColumnas()) {
        VectorMapMatrix result(cantFilas(), cantColumnas());
        while (f < cantFilas()) {
            while (c < cantColumnas()) {
                result.asignar(f, c, at(f, c) + B.at(f, c));
                c++;
            }
            c=0;
            f++;
        }
        return result;
    } else {
        VectorMapMatrix result; //no se puede operar, devuelvo matriz 0x0.
        return result;
    }
    /*if(cantFilas() == B.cantFilas() and cantColumnas() == B.cantColumnas()) {
        VectorMapMatrix result(cantFilas(), cantColumnas());
        map<uint, double>::const_iterator it1 = m[0].begin();
        map<uint, double>::const_iterator it2 = B.m[0].begin();
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
    }*/
}

VectorMapMatrix VectorMapMatrix::operator*(const VectorMapMatrix &B) {
    if(cantColumnas() == B.cantFilas()) {
        VectorMapMatrix result(cantFilas(), B.cantColumnas());
        vector<vector<double> > sumasParciales(cantColumnas(),vector<double>(B.cantColumnas(), 0));
        uint f = 0; //Recorro sobre A, y cuando estoy en el elemento a(ij) multiplico por la fila j de B, sumándolo en result.
        while(f < cantFilas()) {
            map<uint, double>::const_iterator it1 = m[f].begin();
            while (it1 != m[f].end()) {
                map<uint, double>::const_iterator it2 = B.m[it1->first].begin(); //Si el it1 esta en columna j, creo it2 en fila j.
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
            map<uint, double>::iterator hint_iterator = result.m[f].end();
            while(c < sumasParciales[f].size()){
                if(sumasParciales[f][c] != 0) {
                    result.m[f].insert(hint_iterator,make_pair(c, sumasParciales[f][c])); //como el elemento a insertar debe ir al final,
                }
                // le doy el hint que empiece por alli.
                c++; //cplusplus
            }
            c=0;
            f++;
        }
        return result;
    } else {
        return VectorMapMatrix(); //No existe solución.
    }
}

VectorMapMatrix VectorMapMatrix::mult(VectorMapMatrix const &B){
    if(cantColumnas() == B.cantFilas()) {
        VectorMapMatrix result(cantFilas(), B.cantColumnas());
        for(uint i = 0; i < cantFilas(); ++i) { //Recorro las filas de A.
            for (auto it1 = m[i].cbegin(); it1 != m[i].cend(); ++it1) { //Recorro la i-ésima fila de A.
                for(auto it2 = B.m[it1->first].begin(); it2 != B.m[it1->first].end(); ++it2) {  //Si el it1 esta en columna j, recorro la fila j de B.
                    double sumando = it1->second * it2->second;  //"sumando" es a_ik*b_kj donde i = "i", k = "it1->first" y j = "it2->first".
                    auto it_res = result.m[i].find(it2->first); //Me fijo que hay en res_ij (= a_i1*b_1j + ... + a_i(k-1)*b_(k-1)j )
                    if(it_res == result.m[i].end()) //Si no estaba definido (era 0)...
                        result.m[i][it2->first] = sumando;  //lo defino como a_ik*b_kj.
                    else{   //Si sí estaba definido (no era 0)...
                        if(it_res->second - sumando == 0)   //pero al sumarle a_ik*b_kj va a dar 0...
                            result.m[i].erase(it_res);      //lo borro (vale 0);
                        else                                //y si no va a dar 0...
                            it_res->second += sumando;      //le sumo a_ik*b_kj.
                    }
                }
            }
        }
        return result;
    } else {
        return VectorMapMatrix(); //No está definida la multiplicación.
    }
}

void VectorMapMatrix::operator*(double valor) {
    double acum = 0;
    for (unsigned int f = 0; f<cantFilas(); f++) {
        map<uint, double>::iterator row_iterator = m[f].begin();
        while (row_iterator != m[f].end()) {
            if (valor != 0) {
                row_iterator->second *= valor;
            } else {
                m[f].erase(row_iterator);
            }
            row_iterator++;
        }
    }
}

VectorMapMatrix VectorMapMatrix::triangularMatriz() {}

VectorMapMatrix VectorMapMatrix::permutar(unsigned int j, unsigned int i){
    VectorMapMatrix p = VectorMapMatrix(cantFilas(),width);
    for (unsigned int k = 0; k<cantFilas(); k++){ //genero la matriz de permutacion
        if (k!=i && k!=j){
            p.asignar(k, k, 1);
        } else if (k==i){
            p.asignar(j, k, 1);
        } else {
            p.asignar(i, k, 1);
        }
    }
    return p;



}

pair<vector<double>,short> VectorMapMatrix::EG(const VectorMapMatrix &mat, vector<double> bb) {
	unsigned int i,j,l;
	vector<double> res(width,0);
	short status = 0; //status default, el sistema tiene una unica solucion posible
	double A_kk, A_jk;
	VectorMapMatrix copy = VectorMapMatrix(mat);
	//VectorMapMatrix Mk = VectorMapMatrix(cantFilas(),width);
	bool cont = false; //el bool da es false si en toda la columna de i en adelante es 0, es decir me tengo que saltear este paso
	/*for(i = 0; i < copy.cantFilas(); i++){
		Mk.asignar(i,i,1.0);
	}*/
	for(i = 0; i < copy.cantFilas()-1; i++){ //itero sobre las filas, excepto la ultima porque ahi no tengo que hacer nada
		for(j = i; j < copy.cantFilas(); j++){ //itero sobre las filas desde i en adelante, estaria por fijarme si tengo que hacer o no calculo en el paso i de la EG
			if(copy.at(j,i) != 0){ //si no hay un 0 en la posicion j,i
				cont = true;
				if(copy.at(i,i) == 0){
					copy[i].swap(copy[j]); //cambio de lugar las filas porque habia un 0 en la diagonal pero no en el resto de la columna
                    double temp = bb[i];
                    bb[i] = bb[j];         //como se cambiaron de lugar las filas, también se cambian de lugar los valores de "bb"
                    bb[j] = temp;
                }
				break;
			}
		}
		A_kk = copy.at(i,i);
		for(j = i + 1; j < copy.cantFilas(); j++){ //cálculo del paso i si corresponde
			if (!cont){break;} //si me tengo que saltear este paso no calculo nada
			if(copy.at(j,i) != 0){
				A_jk = copy.at(j,i);
				map<uint, double>::const_iterator it1 = m[f].begin();
				while(it1 != m[f].end()){
					l = it1->first;
					copy.asignar(j,l,copy.at(j,l)-(copy.at(i,l)*A_jk/A_kk));
					it1++;
				}
				bb[j] -= A_jk/A_kk*bb[i]; //no me olvido de actualizar el vector b
			} //A_jk y A_kk son los valores que determinan a las matrices Mk que uso para llegar desde A a U, sabiendo que PA = LU
		}
		if(cont){
			//copy = Mk*copy;
			/*for(j = i + 1; j < copy.cantFilas(); j++){ //revierto la matriz Mk a I
				Mk.asignar(j,i,0.0);
			}*/
			cont = false;
		}
		
	}
	for(i = 0; i < copy.cantFilas(); i++){
		j = copy.cantFilas()-1-i; 
		if(copy.at(j,j) == 0 && bb[j] != 0){
			status = -1; //el sistema es incompatible
			break;
		}
		if(copy.at(j,j) == 0 && bb[j] == 0){
			status = 1; //hay infinitos resultados
			res[j] = 0;
		}
		else{
			res[j] = bb[j]/copy.at(j,j); //tengo A_jj*x_j = b_j, paso dividiendo el A_jj
			
			if (j!=0){
				for(unsigned int l = 0; l < j; l++){
					bb[l] = bb[l] - res[j]*copy.at(l,j); //esto es importante, al b_l con l de 0 a j-1 le paso restando el A_lj*x_j, porque ya conozco el resultado de X_j, de forma que en la siguiente iteracion solo voy a tener algo de esta pinta A_jj*x_j = b_j
				}
			}
		}
	}
	return make_pair(res,status);
}

pair<vector<double>,short> VectorMapMatrix::EGPP(vector<double> bb) {
    unsigned int i,j;
    vector<double> res(width);
    short status = 0; //status default, el sistema tiene una unica solucion posible
    VectorMapMatrix copy = VectorMapMatrix(*this);
    for(i = 0; i < copy.cantFilas()-1; i++){ //itero sobre las filas, excepto la ultima porque ahi no tengo que hacer nada
        double maximo_abs = copy.at(i,i);    //en cada iteración es igual al número más grande (en valor absoluto) del resto de la columna.
        unsigned int fila_del_maximo = i;
        list<pair<uint, double> > filas_a_ser_restadas;
        auto iter_de_la_lista_apuntando_al_maximo = filas_a_ser_restadas.begin();
        for(j = i+1; j < copy.cantFilas(); ++j){ //itero sobre las filas desde i+1 en adelante, para encontrar el valor de "maximo_abs".
            // De paso me guardo las filas en las que encuentro un valor != 0 en la columna "i" y me guardo dicho valor.
            map<unsigned int, double>::const_iterator iter = copy[j].find(i);
            if (iter != copy[j].cend()){    //Si el valor está definido, ie, es != 0:
                const double& a_ji = iter->second;        //lo llamo a_ji y...
                filas_a_ser_restadas.emplace_back(j, a_ji);  //guardo la fila en la que está y su valor.
                if(fabs(a_ji) > fabs(maximo_abs)){ //busco el máximo en valor absoluto
                    maximo_abs = a_ji;
                    fila_del_maximo = j;
                    iter_de_la_lista_apuntando_al_maximo = --filas_a_ser_restadas.end(); //El máximo es el último agregado.
                }
            }
        }
        if(maximo_abs != 0) {    //Si el resto de la columna son todos 0´s (maximo == 0) no necesito hacer más nada. Si hay algún valor no nulo:
            copy[i].swap(copy[fila_del_maximo]); //cambio de lugar las filas para que a_ii sea el número con valor absoluto más grande.
            swap(bb[i], bb[j]);                  //como se cambiaron de lugar las filas, también se cambian de lugar los valores de "bb"
            filas_a_ser_restadas.erase(iter_de_la_lista_apuntando_al_maximo);//También debo sacar de la lista de filas a restar, aquella que contiene al máximo y...
            if (filas_a_ser_restadas.begin()->first == i)    //si la fila "i" está en la lista...
                filas_a_ser_restadas.begin()->first = fila_del_maximo;    //debe actualizarse el índice de su fila (pues la swapé).
            double& a_ii = maximo_abs;
            for (auto iter_lista = ++filas_a_ser_restadas.begin(); iter_lista != filas_a_ser_restadas.end(); ++iter_lista) {
                double& a_ji = iter_lista->second;
                copy.resta_de_filas(iter_lista->first, a_ji / a_ii, i);
            }
        }
    }
    for(i = 0; i < copy.cantFilas(); i++){
        j = copy.cantFilas()-1-i;
        double a_jj = copy.at(j,j);
        if(a_jj == 0 && bb[j] != 0){
            status = -1; //El sistema es incompatible.
            break;
        }
        if(a_jj == 0 && bb[j] == 0){
            status = 1; //Hay infinitos resultados.
            res[j] = 0;
        }
        else{
            res[j] = bb[j]/a_jj; //Tengo a_jj*x_j = b_j, paso dividiendo el a_jj
            for(unsigned int l = 0; l < j; l++){    //Esto es importante, al b_l con l de 0 a j-1 le paso restando el a_lj*x_j, porque ya conozco...
                bb[l] -= res[j]*copy.at(l,j);  //el resultado de x_j, de forma que en la siguiente iteracion solo voy a tener algo de esta pinta A_jj*x_j = b_j
            }
        }
    }
    return make_pair(res,status);
}

void VectorMapMatrix::resta_de_filas(uint fila_a_modificar, double escalar, uint fila_para_restar){
    if(escalar == 0) return;
    else {
        auto it1 = m[fila_a_modificar].begin();
        auto fin1 = m[fila_a_modificar].end();
        auto it2 = m[fila_para_restar].begin();
        auto fin2 = m[fila_para_restar].end();
        while (it2 != fin2) {  //Mientras no haya acabado la fila para restar:
            double resultado_de_la_resta = -escalar * (it2->second); //empiezo restando lo que hay que restar
            while (it1 != fin1 && it1->first < it2->first) ++it1;
            if (it1->first == it2->first) resultado_de_la_resta += it1->second; //si hay algo distinto de 0 en la coordenada a modificar, lo sumo
            if (resultado_de_la_resta != 0) m[fila_a_modificar][it2->first] = resultado_de_la_resta;    //si el resultado de la resta no es 0, lo defino en el diccionario/fila
            ++it2;
        }
    }
}
/*
 * Funciones para mostrar la matriz
 */

string convertirAString(double num) {
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

string agregarEspacios(double valor, int cantidadMaxima) {
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
