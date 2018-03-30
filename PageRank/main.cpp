#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <stdlib.h>
#include "Matriz.h"
#include "Util.cpp"



Matriz getMatrizProbabilidad(int sizeFila, int sizeColumna, float p) {
    Matriz ret(sizeFila, sizeColumna);
    for (int i=0; i < sizeFila; i++) {
        for (int j=0; j<sizeColumna; j++) {
            if (i=j)
                ret.set(i, j, p);
        }
    }
    return ret;
}

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

Matriz getMatrizPuntajesPonderados(Matriz &W) {
    Matriz ret(W.sizeFila, W.sizeColumna);
    float acum;
    for (int j=0; j<W.sizeColumna; j++) {
        acum = 0;
        for (int i=0; i < W.sizeFila; i++) {
            acum += W.get(i, j);
        }
        if (acum != 0)
            ret.set(j, j, 1 / acum);
    }
    return ret;

}

Matriz getVectorProbabilidadesDeSalto(Matriz &D, float p) {
    Matriz ret(1, D.sizeColumna);
    int n = D.sizeColumna;
    for (int j=0; j<D.sizeColumna; j++) {
        if (D.get(j,j) != 0)
            ret.set(1, j, (1-p)/n);
        else
            ret.set(1, j, 1/n);
    }
    return ret;
}

Matriz getMatrizIdentidad(int tamano) {
    Matriz ret(tamano, tamano);
    for (int i=0; i<tamano; i++) {
        ret.set(i, i, 1);
    }
    return ret;
}

/**
 * Aca implementacion del PageRank
 * @param matrizDeConectividad la matriz con los links entre las paginas
 * @return devuelve el ranking.
 */
std::vector<float> pageRank(Matriz &W, float probabilidadDeSaltar) {

    std::vector<float> ranking(5);
    cout << "Matriz W antes: \n";
    cout << "\n" << W << "\n\n";
    W * probabilidadDeSaltar;
    cout << "Matriz W despues: \n";
    cout << "\n" << W << "\n\n";


    //p tiene que ser un numero
    Matriz D = getMatrizPuntajesPonderados(W);
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

        Matriz matrizDeConectividad = leerMatriz(nombreArchivo);

       std::vector<float> ranking = pageRank(matrizDeConectividad, probabilidadDeSaltar);

        escribirRanking(nombreArchivo + ".out", ranking, probabilidadDeSaltar);
    }

    return 0;
}

