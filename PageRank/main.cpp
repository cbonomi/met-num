#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <stdlib.h>
#include "Matriz.h"
#include "Util.h"
#include "rdtsc.h"

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
    for (unsigned int j=0; j<W.cantColumnas(); j++) {
        acum = 0;
        for (unsigned int i=0; i < W.cantFilas(); i++) {
            acum += W.at(i, j);
        }
        if (acum != 0)
            ret.asignar(j, j, 1 / acum);
    }
    return ret;

}

VectorMapMatrix getVectorProbabilidadesDeSalto(VectorMapMatrix &D, float p) {
    VectorMapMatrix ret(1, D.cantColumnas());
    float n = D.cantColumnas();
    for (unsigned int j=0; j<D.cantColumnas(); j++) {
        if (D.at(j,j) != 0)
            ret.asignar(0, j, (float)((1-p)/n));
        else
            ret.asignar(0, j, (float)(1/n));
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


vector<float> getb(int tamano) {
    vector<float> ret(tamano);
    for (int i=0; i<tamano; i++) {
        ret.assign(i, 1);
    }
    return ret;
}


void mostrar(vector<float> v) {
    for (int i=0; i<v.size(); i++)
        cout << v.at(i) << "\n";
}

/**
 * Aca implementacion del PageRank
 * @param matrizDeConectividad la matriz con los links entre las paginas
 * @return devuelve el ranking.
 */
vector<float> pageRank(VectorMapMatrix &W, float probabilidadDeSaltar) {

    //   vector<float> ranking(5);
    cout << "Matriz W antes: \n";
    cout << "\n" << W << "\n\n";
//    cout << "Matriz W despues: \n";
//    cout << "\n" << W << "\n\n";


    //
    VectorMapMatrix D = getMatrizPuntajesPonderados(W);
    cout << "Matriz D: \n";
    cout << D << "\n\n";

    VectorMapMatrix DW = D*W;
    cout << "Matriz DW: \n";
    cout << DW << "\n\n";

    DW * probabilidadDeSaltar;

    cout << "Matriz pDW: \n";
    cout << DW << "\n\n";



    VectorMapMatrix z = getVectorProbabilidadesDeSalto(D, probabilidadDeSaltar);
//    cout << "Matriz z: \n";
//    cout << z << "\n\n";
    VectorMapMatrix I = getMatrizIdentidad(W.cantFilas());
    cout << "Matriz I: \n";
    cout << I << "\n\n";
    DW * (-1);
    cout << "Matriz -DW: \n";
    cout << DW << "\n\n";

    VectorMapMatrix I_pWD = I + DW;
    cout << "Matriz I_pWD: \n";
    cout << I_pWD << "\n\n";



    vector<float> b = getb(I_pWD.cantFilas());

//    cout << "termino independiente: \n";
//    mostrar(terminoIndependiente);


/*    float matriz[ORDEN][4]={
            {0.0375, 0.465, 0.465, 0.0375},
            {0.0375, 0.8875, 0.0375, 0.0375},
            {0.0375, 0.465, 0.0375, 0.465},
            {0.0375, 0.0375, 0.0375, 0.8875}
    };
*/
    VectorMapMatrix matrizPrueba();

    W.asignar(0, 0, 0.0375);
    W.asignar(0, 1, 0.465);
    W.asignar(0, 2, 0.465);
    W.asignar(0, 3, 0.0375);
    W.asignar(1, 0, 0.0375);
    W.asignar(1, 1, 0.8875);
    W.asignar(1, 2, 0.0375);
    W.asignar(1, 3, 0.0375);
    W.asignar(2, 0, 0.0375);
    W.asignar(2, 1, 0.465);
    W.asignar(2, 2, 0.0375);
    W.asignar(2, 3, 0.465);
    W.asignar(3, 0, 0.0375);
    W.asignar(3, 1, 0.0375);
    W.asignar(3, 2, 0.0375);
    W.asignar(3, 3, 0.8875);

    pair<vector<float>,short> ranking = D.EG(D, b);

//    cout << "ranking: \n";
    vector<float> rk = ranking.first;

//    cout << "status: " << ranking.second;

    mostrar(rk);



/*    ranking.push_back(0.4);
    ranking[1] = 0.1;
    ranking[2] = 0.2;
    ranking[3] = 0.15;
    ranking[4] = 0.15;*/
    return ranking.first;
}


int main(int argc, char * argv[]) {

    if (argc != 3) {
        cout << "Modo de uso: tp1 archivo p\n";
    } else {
        string nombreArchivo = argv[1];

        float probabilidadDeSaltar = atof(argv[2]);

        VectorMapMatrix matrizDeConectividad = leerMatriz(nombreArchivo);

        unsigned long start, end;
        unsigned long startm, endm;
        RDTSC_START(start);
        vector<float> ranking = pageRank(matrizDeConectividad, probabilidadDeSaltar);
        RDTSC_STOP(end);
        unsigned long delta = end - start;
        cout << delta;

        escribirRanking(nombreArchivo + ".out", ranking, probabilidadDeSaltar);
    }

    return 0;
}

