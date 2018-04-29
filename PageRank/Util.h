#ifndef PAGERANK_UTIL_CPP
#define PAGERANK_UTIL_CPP

#include "VectorMapMatrix.h"

pair<VectorMapMatrix, VectorMapMatrix> leerMatrizYMatrizTraspuesta(string nombreArchivo);
void escribirRanking(string nombreArchivo, vector<double> ranking, double probabilidadDeSaltar);

#endif