#ifndef PAGERANK_MAPMATRIX_H
#define PAGERANK_MAPMATRIX_H

#include <map>
using namespace std;

class MapMatrix {
public:
    MapMatrix(); //constructor por defecto

    MapMatrix(uint h, uint w); //Nueva matriz "Llena de ceros" de altura h, ancho w.

    MapMatrix(const MapMatrix & orig) = default; //default copy constructor

    ~MapMatrix() = default; //destructor por defecto

    float & operator[](const pair<uint, uint> & p);

    MapMatrix sumaMatrices(const MapMatrix & A, const MapMatrix & B);

    MapMatrix productoMatrices();

    MapMatrix triangularMatriz();
private:
    map<pair<uint,uint>, float> m; //La matriz va a tener posiciones i, j enteras sin signo, y en esa posicion va a
    // tener un float (la matriz va a realizar ecuaciones con floats).
    uint width;
    uint height;
};


#endif //PAGERANK_MAPMATRIX_H
