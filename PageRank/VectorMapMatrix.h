#ifndef PAGERANK_VECTORMAPMATRIX_H
#define PAGERANK_VECTORMAPMATRIX_H

#include <map>
#include <vector>

using namespace std;

class VectorMapMatrix {
public:
    VectorMapMatrix(); //Construyo una "matriz" de 0x0

    VectorMapMatrix(uint h, uint w); //Nueva matriz "Llena de ceros" de altura h, ancho w.

    VectorMapMatrix(const VectorMapMatrix &orig) = default; //default copy constructor

    VectorMapMatrix& operator=(const VectorMapMatrix &orig) = default; //default operador de asignacion

    ~VectorMapMatrix() = default; //destructor por defecto

    size_t cantFilas() const;

    size_t cantColumnas() const;

    void asignar(uint f, uint c, const float value); //Si el valor a asignar puede o no ser 0, usar esta función (y no operator[]).

    const float at(uint f, uint c) const; //útil si queres leer la posición sin asignar un 0 (operator[] crea el nodo sin importar si no asignas nada).

    float& operator[](pair<uint,uint> p); //Usar solo si se quieren hacer muchas asignaciones distintas de 0.
    // Cuidado, no usar para asignar ceros, usar asignar en tal caso.

	map<uint, float>& operator[](uint i){ return m[i]; }; //Devuelve una referencia a la i-esima fila.

    VectorMapMatrix operator+(VectorMapMatrix const &B);

    VectorMapMatrix operator*(VectorMapMatrix const &B);

    VectorMapMatrix mult(VectorMapMatrix const &B);

    void operator*(float valor);

    VectorMapMatrix triangularMatriz();

	pair<vector<float>,short> EG(const VectorMapMatrix& mat, vector<float> b);

	pair<vector<float>,short> EGPP(vector<float>);
	
	VectorMapMatrix permutar(unsigned int j, unsigned int i);
private:
    vector<map<uint, float> > m; //La matriz va a tener un vector vertical, de arboles rojo negro horizontales.
    size_t width;

    void resta_de_filas(uint fila_a_modificar, float escalar, uint fila_para_restar);
};

ostream& operator << (ostream &o, VectorMapMatrix &B);

#endif //PAGERANK_VECTORMAPMATRIX_H
