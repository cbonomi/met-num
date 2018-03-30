#include "VectorMapMatrix.h"
#include <fstream>
#include "Util.h"

using namespace std;

VectorMapMatrix leerMatriz(string nombreArchivo) {
    fstream entrada(nombreArchivo, ios_base::in);

    int cantidadTotalDePaginas;
    int cantidadTotalDeLinks;


    entrada >> cantidadTotalDePaginas >> cantidadTotalDeLinks;

    VectorMapMatrix ret(cantidadTotalDePaginas, cantidadTotalDeLinks);

    int i, j;

    while (entrada >> i >> j)
        ret.asignar(i, j, 1);

    entrada.close();

    return ret;
}

void escribirRanking(string nombreArchivo, vector<float> ranking, float probabilidadDeSaltar) {
    ofstream salida(nombreArchivo, ios_base::out);

    salida << probabilidadDeSaltar << '\n';

    for (vector<float>::iterator it = ranking.begin() ; it != ranking.end(); ++it)
        salida << *it << '\n';

    salida.close();
}
