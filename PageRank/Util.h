#ifndef PAGERANK_UTIL_CPP
#define PAGERANK_UTIL_CPP

#include "VectorMapMatrix.h"

VectorMapMatrix leerMatriz(string nombreArchivo);
void escribirRanking(string nombreArchivo, vector<float> ranking, float probabilidadDeSaltar);

#endif