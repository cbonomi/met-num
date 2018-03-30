#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <stdlib.h>
#include "Matriz.h"
#include "Util.h"

using namespace std;

/*Matriz getMatrizProbabilidad(int sizeFila, int sizeColumna, float p) {
    Matriz ret(sizeFila, sizeColumna);
    for (int i=0; i < sizeFila; i++) {
        for (int j=0; j<sizeColumna; j++) {
            if (i=j)
                ret.set(i, j, p);
        }
    }
    return ret;
}*/

/*Matriz getVectorLinksSalientes(Matriz W) {
    Matriz ret(W.sizeFila, 1);
    float acum;
    for (int j=0; j<W.sizeColumna; j++) {
        acum = 0;
        for (int i=0; i < W.sizeFila; i++) {
            acum += W.get(i, j);
            ret.set(i, j, p);
        }
        ret.set(j, 0, acum);
    }
    return ret;
}*/

VectorMapMatrix getMatrizPuntajesPonderados(VectorMapMatrix &W) {
    VectorMapMatrix ret(W.cantFilas(), W.cantColumnas());
    float acum;
    for (int j=0; j<W.cantColumnas(); j++) {
        acum = 0;
        for (int i=0; i < W.cantFilas(); i++) {
            acum += W.at(i, j);
        }
        if (acum != 0)
            ret.asignar(j, j, 1 / acum);
    }
    return ret;

}

VectorMapMatrix getVectorProbabilidadesDeSalto(VectorMapMatrix &D, float p) {
    VectorMapMatrix ret(1, D.cantColumnas());
    int n = D.cantColumnas();
    for (int j=0; j<D.cantColumnas(); j++) {
        if (D.at(j,j) != 0)
            ret.asignar(1, j, (1-p)/n);
        else
            ret.asignar(1, j, 1/n);
    }
    return ret;
}

VectorMapMatrix getMatrizIdentidad(int tamano) {
    VectorMapMatrix ret(tamano, tamano);
    for (int i=0; i<tamano; i++) {
        ret.asignar(i, i, 1);
    }
    return ret;
}

/**
 * Aca implementacion del PageRank
 * @param matrizDeConectividad la matriz con los links entre las paginas
 * @return devuelve el ranking.
 */
vector<float> pageRank(VectorMapMatrix &W, float probabilidadDeSaltar) {

    vector<float> ranking(5);
    cout << "Matriz W antes: \n";
    cout << "\n" << W << "\n\n";
    W * probabilidadDeSaltar;
    cout << "Matriz W despues: \n";
    cout << "\n" << W << "\n\n";


    //p tiene que ser un numero
    VectorMapMatrix D = getMatrizPuntajesPonderados(W);
    cout << "Matriz D: \n";
    cout << D << "\n\n";
/*    Matriz z = getVectorProbabilidadesDeSalto(D, probabilidadDeSaltar);
    cout << "Matriz z: \n";
    cout << z << "\n\n";
    Matriz I = getMatrizIdentidad(W.sizeFila);
    cout << "Matriz I: \n";
    cout << I << "\n\n";
*/


    ranking.push_back(0.4);
    ranking[1] = 0.1;
    ranking[2] = 0.2;
    ranking[3] = 0.15;
    ranking[4] = 0.15;
    return ranking;
}


int main(int argc, char * argv[]) {

    if (argc != 3) {
        cout << "Modo de uso: tp1 archivo p\n";
    } else {
        string nombreArchivo = argv[1];

        float probabilidadDeSaltar = atof(argv[2]);

        VectorMapMatrix matrizDeConectividad = leerMatriz(nombreArchivo);

        vector<float> ranking = pageRank(matrizDeConectividad, probabilidadDeSaltar);

        escribirRanking(nombreArchivo + ".out", ranking, probabilidadDeSaltar);
    }

    return 0;
}

