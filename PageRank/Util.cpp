#include "VectorMapMatrix.h"
#include <fstream>
#include "Util.h"

using namespace std;

pair<VectorMapMatrix, VectorMapMatrix> leerMatrizYMatrizTraspuesta(string nombreArchivo) {
    fstream entrada(nombreArchivo, ios_base::in);

    int cantidadTotalDePaginas;
    int cantidadTotalDeLinks;


    entrada >> cantidadTotalDePaginas >> cantidadTotalDeLinks;

    VectorMapMatrix matriz(cantidadTotalDePaginas, cantidadTotalDePaginas);
    VectorMapMatrix matrizTras(cantidadTotalDePaginas, cantidadTotalDePaginas);

    int i, j;

    for (int k = 0; k<cantidadTotalDeLinks; ++k) {
        entrada >> j >> i;
        matriz.asignar(i-1, j-1, 1);
        matrizTras.asignar(j-1, i-1, 1);
    }

    entrada.close();

    return make_pair(matriz, matrizTras);
}

void escribirRanking(string nombreArchivo, vector<double> ranking, double probabilidadDeSaltar) {
    ofstream salida(nombreArchivo, ios_base::out);

    salida << probabilidadDeSaltar << '\n';

    for (vector<double>::iterator it = ranking.begin() ; it != ranking.end(); ++it)
        salida << *it << '\n';

    salida.close();
}

VectorMapMatrix leerMatriz(string nombreArchivo) {
    fstream entrada(nombreArchivo, ios_base::in);

    int cantidadTotalDePaginas;
    int cantidadTotalDeLinks;


    entrada >> cantidadTotalDePaginas >> cantidadTotalDeLinks;

    VectorMapMatrix ret(cantidadTotalDePaginas, cantidadTotalDePaginas);

    int i, j;

    for (int k = 0; k<cantidadTotalDeLinks; k++) {
        entrada >> i >> j;
        ret.asignar(j-1, i-1, 1);
    }

    entrada.close();

    return ret;
}