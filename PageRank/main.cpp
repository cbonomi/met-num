#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <stdlib.h>
#include <algorithm>
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
}

Matriz getVectorLinksSalientes(Matriz W) {
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

VectorMapMatrix getMatrizDiagonal(VectorMapMatrix &W) {
    VectorMapMatrix ret(W.cantFilas(), W.cantColumnas());
    double acum[W.cantColumnas()];
    for(uint i = 0; i < W.cantColumnas(); ++i)      acum[i] = 0;
    for (unsigned int i=0; i<W.cantFilas(); ++i) {
        for(auto it = W[i].begin(); it != W[i].end(); ++it)     acum[it->first] += it->second;
    }
    for(uint i = 0; i < ret.cantFilas(); ++i)   ret.asignar(i, i, (acum[i] != 0 ? 1/acum[i] : 0));
    return ret;

}

VectorMapMatrix getVectorProbabilidadesDeSalto(VectorMapMatrix &D, double p) {
    VectorMapMatrix ret(1, D.cantColumnas());
    double n = D.cantColumnas();
    for (unsigned int j=0; j<n; j++) {
        if (D.at(j,j) != 0)
            ret.asignar(0, j, (double)((1-p)/n));
        else
            ret.asignar(0, j, (double)(1/n));
    }
    return ret;
}

VectorMapMatrix getMatrizIdentidad(uint tamano) {
    VectorMapMatrix ret(tamano, tamano);
    for (uint i=0; i<tamano; i++) {
        ret.asignar(i, i, 1);
    }
    return ret;
}

/*
vector<double> getb(uint tamano) {
    vector<double> ret(tamano);
    for (int i=0; i<tamano; i++) {
        ret.assign(i, 1);
    }
    return ret;
}
*/

void mostrar(vector<double> v) {
    for (int i=0; i<v.size(); i++)
        cout << v.at(i) << "\n";
}

double sumar(vector<double> v) {
    std::sort(v.begin(), v.end());      //Lo ordeno porque se van a sumar solo números positivos, y sumarlos en orden es
    double suma = 0;                    //la forma más precisa de calcular la suma exacta.
    for (int i=0; i<v.size(); i++)
        suma += v[i];
    return suma;
}

vector<double> dividir(vector<double> v, double num) {
    vector<double> ret(v.size());
    for (int i=0; i<v.size(); i++)
        ret[i] = v[i]/num;
    return ret;
}

/**
 * Aca implementacion del PageRank
 * @param matrizDeConectividad la matriz con los links entre las paginas
 * @return devuelve el ranking.
 */
vector<double> pageRank(VectorMapMatrix &W, double probabilidadDeSaltar) {

    //   vector<float> ranking(5);
    cout << "Matriz W antes: \n";
    cout << "\n" << W << "\n\n";
//    cout << "Matriz W despues: \n";
//    cout << "\n" << W << "\n\n";


    //
    VectorMapMatrix D = getMatrizDiagonal(W);
    cout << "Matriz D: \n";
    cout << D << "\n\n";

    VectorMapMatrix DW = D*W;
    cout << "Matriz DW: \n";
    cout << DW << "\n\n";

    DW * probabilidadDeSaltar;

    cout << "Matriz pDW: \n";
    cout << DW << "\n\n";



    VectorMapMatrix z = getVectorProbabilidadesDeSalto(D, probabilidadDeSaltar);
    cout << "Matriz z: \n";
    cout << z << "\n\n";
    VectorMapMatrix I = getMatrizIdentidad(W.cantFilas());
//    cout << "Matriz I: \n";
//    cout << I << "\n\n";
    DW * (-1);
    cout << "Matriz -DW: \n";
    cout << DW << "\n\n";

    VectorMapMatrix I_pWD = I + DW;
    cout << "Matriz I_pWD: \n";
    cout << I_pWD << "\n\n";



    vector<double> b(W.cantFilas(), 1);

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

    pair<vector<double>,short> ranking = I_pWD.EG(I_pWD, b);



    //    cout << "ranking: \n";
    vector<double> rk = ranking.first;
    double num = sumar(rk);
    vector<double> rkNorm = dividir(rk, num);


//    cout << "status: " << ranking.second;

    mostrar(rkNorm);
    cout << "------";



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

        double probabilidadDeSaltar = atof(argv[2]);

        VectorMapMatrix matrizDeConectividad = leerMatriz(nombreArchivo);

        unsigned long start, end;
        unsigned long startm, endm;
        RDTSC_START(start);
        vector<double> ranking = pageRank(matrizDeConectividad, probabilidadDeSaltar);
        RDTSC_STOP(end);
        unsigned long delta = end - start;
        cout << delta;

        // escribirRanking(nombreArchivo + ".out", ranking, probabilidadDeSaltar);
    }

    return 0;
}

