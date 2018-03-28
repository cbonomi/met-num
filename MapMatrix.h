#ifndef PAGERANK_MAPMATRIX_H
#define PAGERANK_MAPMATRIX_H

#include <map>
#include <vector>

using namespace std;

class MapMatrix {
public:
    MapMatrix(); //Construyo una "matriz" de 0x0

    MapMatrix(uint h, uint w); //Nueva matriz "Llena de ceros" de altura h, ancho w.

    MapMatrix(const MapMatrix &orig) = default; //default copy constructor

    ~MapMatrix() = default; //destructor por defecto

    uint cantFilas() const;

    uint cantColumnas() const;

    void asignar(const pair<uint, uint> p, const float value); //Si el valor a asignar puede o no ser 0, usar esta función (y no operator[]).

    const float at(const pair<uint, uint> p) const; //útil si queres leer la posición sin asignar un 0 (operator[] crea el nodo sin importar si no asignas nada).

    float & operator[](const pair<uint, uint> &p); //Usar solo si se quieren hacer muchas asignaciones distintas de 0.
    // Cuidado, no usar para asignar ceros, usar asignar en tal caso.

    MapMatrix sumaMatrices(const MapMatrix &A, const MapMatrix &B);

    MapMatrix productoMatrices(const MapMatrix &A, const MapMatrix &B);

    MapMatrix triangularMatriz();
private:
    map<pair<uint,uint>, float> m; //La matriz va a tener posiciones i, j enteras sin signo, y en esa posicion va a
    // tener un float (la matriz va a realizar ecuaciones con floats).
    vector<vector<bool> > esCero;
    uint width;
    uint height;
};


#endif //PAGERANK_MAPMATRIX_H
