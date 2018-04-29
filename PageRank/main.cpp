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


bool MEDIR = true;

unsigned int CANTIDAD_MEDICIONES = 1;


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

VectorMapMatrix getTraspuesta(VectorMapMatrix &W) {
    VectorMapMatrix ret(W.cantFilas(), W.cantColumnas());
    double acum[W.cantColumnas()];
    for(uint i = 0; i < W.cantColumnas(); ++i)
        for (unsigned int j=0; j<W.cantFilas(); ++j)
            ret.asignar(j, i, W.at(i, j));
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

vector<double> normalizar(pair<vector<double>,short> ranking) {
    vector<double> rk = ranking.first;
    double num = sumar(rk);
    vector<double> rkNorm = dividir(rk, num);
    return rkNorm;
}

/**
 * Aca implementacion del PageRank
 * @param matrizDeConectividad la matriz con los links entre las paginas
 * @return devuelve el ranking.
 */
vector<double> pageRank(VectorMapMatrix &W, VectorMapMatrix &Wt, double probabilidadDeSaltar) {

    VectorMapMatrix D = getMatrizDiagonal(W);

    VectorMapMatrix WD = W*D;
    
    VectorMapMatrix DWt = D*Wt;

    WD * (-probabilidadDeSaltar);
    
    DWt * (-probabilidadDeSaltar);

    VectorMapMatrix I = getMatrizIdentidad(W.cantFilas());

    VectorMapMatrix I_pWD = I + WD;
    
    VectorMapMatrix I_pDWt = I + DWt;

    vector<double> b(W.cantFilas(), 1);

    //if (MEDIR) {
        //unsigned long delta = 0;
        //pair<vector<double>,short> ranking;
        //for (int i = 0; i < CANTIDAD_MEDICIONES; i++) {
            //unsigned long start, end;
            //RDTSC_START(start);
            pair<vector<double>,short> ranking = I_pWD.EG(I_pWD, I_pDWt, b);
           // RDTSC_STOP(end);
            //delta += end - start;
            vector<double> rn = normalizar(ranking);
        //}
       // cout << delta / CANTIDAD_MEDICIONES;
    //}

    //pair<vector<double>,short> ranking = I_pWD.EG(I_pWD, b);
    //vector<double> rn = normalizar(ranking);
    //mostrar(rn);
    return rn;
}


int main(int argc, char * argv[]) {

    if (argc != 3) {
        cout << "Modo de uso: tp1 archivo p\n";
    } else {
        string nombreArchivo = argv[1];

        double probabilidadDeSaltar = atof(argv[2]);

        pair<VectorMapMatrix, VectorMapMatrix> matrizDeConectividad = leerMatrizYMatrizTraspuesta(nombreArchivo);

        vector<double> ranking = pageRank(matrizDeConectividad.first, matrizDeConectividad.second, probabilidadDeSaltar);

        escribirRanking(nombreArchivo + ".out", ranking, probabilidadDeSaltar);
    }

    return 0;
}

