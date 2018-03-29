#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <stdlib.h>
#include "Matriz.h"
#include "Util.cpp"

/**
 * Aca implementacion del PageRank
 * @param matrizDeConectividad la matriz con los links entre las paginas
 * @return devuelve el ranking.
 */
std::vector<float> pageRank(Matriz matrizDeConectividad) {
    std::vector<float> ranking(5);

    cout << "\n" << matrizDeConectividad;

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

       std::vector<float> ranking = pageRank(matrizDeConectividad);

        escribirRanking(nombreArchivo + ".out", ranking, probabilidadDeSaltar);
    }

    return 0;
}
