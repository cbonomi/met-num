#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <stdlib.h>
#include <chrono>
#include "VectorMapMatrix.h"
#include "rdtsc.h"

int main(){
    /*VectorMapMatrix A(8756,3387);
    A.asignar(7,2,54.654);
    A.asignar(7,2,54.654);
    A.asignar(7,2,-5);
    A.asignar(7,2,70);
    A.asignar(7,30,54.654);
    A.asignar(7,2,0);
    A.asignar(7,250,54.654);
    A.asignar(7,2,54.654);
    A.asignar(7,2,54.654);
    A.asignar(7,32,54.654);
    A.asignar(7,2,5.654);
    A.asignar(7,32,0);
    A = VectorMapMatrix(10,10);
    VectorMapMatrix B = VectorMapMatrix(10,10);
    for(int f=0;f<10;f++) {
        for(int c=0; c<10;c++) {
            A.asignar(f,c, 7);
            B.asignar(f,c, 5);
        }
    }
    VectorMapMatrix C = A+B;
    for(int f=0;f<10;f++) {
        for(int c=0; c<10;c++) {
            A.asignar(f,c, 15);
            B.asignar(f,c, 5);
        }
    }
    B*(-3);
    C = A + B;
    for(int f=0;f<10;f++) {
        for(int c=0; c<10;c++) {
            A.asignar(f,c, 15);
            B.asignar(f,c, -15);
        }
    }
    C = A * B;
    VectorMapMatrix I(10,10);
    for(int c=0; c<10;c++) {
        I.asignar(c,c, 1);
    }
    C = B * I;
    C = A * I;
    VectorMapMatrix R(10,300);
    for(float f=0;f<10;f+=1) {
        for(float c=0; c<300;c+=1) {
            R.asignar(f,c, f/(c+1));
        }
    }
    C= A*R;
    C= I*R;*/
///Prueba básica de multiplicación
    VectorMapMatrix M1(1000,1500);
    VectorMapMatrix M2(1500,1200);
    M1.asignar(120, 30, 3.4);
    M2.asignar(30, 500, 2.0);
    M1.asignar(420, 600, 4.5);
    M2.asignar(600, 500, 2.0);
    M1.asignar(420, 700, 9.0);
    M2.asignar(700, 500, -1.0);
//    auto t1 = std::chrono::system_clock::now();
    VectorMapMatrix Res1 = M1*M2;
//    auto t2 = std::chrono::system_clock::now();
//    auto t3 = std::chrono::system_clock::now();
//    VectorMapMatrix Res2 = M1.mult(M2);
//    auto t4 = std::chrono::system_clock::now();
//    std::cout << "El tiempo del oper* dividido el tiempo de la funcion mult es: " << (t2-t1)/(t4-t3) << std::endl;
    std::cout << "Res_(120,500) debe ser 6.8 y dio respectivamente: " << Res1.at(120, 500) /*<< " , " << Res2.at(120, 500) */<< std::endl;
    std::cout << "Res_(420,500) debe ser 0.0 y dio respectivamente: " << Res1.at(420, 500) /*<< " , " << Res2.at(420, 500) */<< std::endl;
///Prueba más completa
    /*VectorMapMatrix M(3, 4);
    VectorMapMatrix N(4, 3);*/
    vector<double> v_M = {1, 3, 5, 6, -0.4, -8.4, 5.9, 16.002, 23, 0.228, 0.003, 7};
    vector<double> v_N = {-0.04, -9.31, -6.77, 4.5, 12.43, 9.04, -8.53, 0.04, -0.73, 6.4, 7.53, -7.89};
    VectorMapMatrix M = vector2matrix(v_M, 3);
    VectorMapMatrix N = vector2matrix(v_N, 4);
    /*
    M = |   1,     3,     5,      6|            N = |-0.04, -9.31, -6.77|
        |-0.4,  -8.4,   5.9, 16.002|                |  4.5, 12.43,  9.04|
        |  23, 0.228, 0.003,      7|                |-8.53,  0.04, -0.73|
                                                    |  6.4,  7.53, -7.89|
    */
    VectorMapMatrix R1 = M*N;
    VectorMapMatrix R2 = N*M;
    /*Según Octave las soluciones son:
     * R1 =    | 9.2100,    73.3600,   -30.6400|            R2 =   |-152.026,    76.540,   -55.149,  -196.609|
               |14.3018,    20.0431,  -203.7908|                   | 207.448,   -88.851,    95.864,   289.185|
               |44.8804,  -158.5858,  -208.8811|                   | -25.336,   -26.092,   -42.416,   -55.650|
                                                                   |-178.082,   -45.851,    76.403,   103.665|
     */
    mostrar_matriz_por_consola(M, "M");
    mostrar_matriz_por_consola(N, "N");
    mostrar_matriz_por_consola(R1, "R1");
    mostrar_matriz_por_consola(R2, "R2");
///Prueba de EGPP con matrices no tan mal condicionadas
    v_M = {5.554425, 2.926709, 1.302525, 0.095282, -3.667271, 11.974929, 4.942541, -3.317605, 1.529675, 3.135779, 8.343999, -0.621217, 0.135427, -4.166134, 2.909134, 7.756480};
    M = vector2matrix(v_M, 4);  //cond(M, 1) = 7.7541; cond(M, Inf) = 8.7856
    mostrar_matriz_por_consola(M, "M");
    vector<double> b1 = {2, 5, -3.45, -1};
    pair<vector<double>, short> x1 = M.EGPP(b1);
    vector<double> sol_MatLab_1 = {0.044086, 0.896596, -0.712414, 0.619079};
    std::cout << std::endl << "Status: " << x1.second;
    mostrar_vector_por_consola(x1.first, "x1");
    mostrar_vector_por_consola(sol_MatLab_1, "sol_MatLab_1");
    vector<double> casi_b1 = M*x1.first;
    mostrar_vector_por_consola(casi_b1, "M*x1");
    vector<double> casi_b1_2 = M*sol_MatLab_1;
    mostrar_vector_por_consola(casi_b1_2, "M*sol_MatLab_1");
    mostrar_vector_por_consola(b1, "b1");

    v_N = {1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1};
    N = vector2matrix(v_N, 4);  //cond(N, 1) = 8; cond(M, Inf) = 8
    mostrar_matriz_por_consola(N, "N");
    vector<double> b2 = {2, 5, -3.45, -1};
    pair<vector<double>, short> x2 = N.EGPP(b2);
    vector<double> sol_MatLab_2 = {2.0000, 3.0000, -8.4500, 2.45000};
    std::cout << std::endl << "Status: " << x2.second;
    mostrar_vector_por_consola(x2.first, "x2");
    mostrar_vector_por_consola(sol_MatLab_2, "sol_MatLab_2");
    vector<double> casi_b2 = N*x2.first;
    mostrar_vector_por_consola(casi_b2, "N*x2");
    vector<double> casi_b2_2 = N*sol_MatLab_2;
    mostrar_vector_por_consola(casi_b2_2, "N*sol_MatLab_2");
    mostrar_vector_por_consola(b1, "b1");
///Prueba con matriz mal condicionada
    //cond(Rand, 1) = 39.900; cond(R2, Inf) = 52.626
    vector<double> v_Rand = { 2.8257,    4.9103,  -14.1120,    2.0861,  -11.3977,
                            -16.3647,  -11.3853,   17.7934,   -1.0902,   -5.9794,
                            -14.9279,   10.4551,   10.2855,   10.5403,   -1.1875,
                              9.5779,   15.2521,    3.6329,  -14.5391,   11.6643,
                            -34.1376,   18.1524,   15.9649,  -19.4520,  -20.2618};
    VectorMapMatrix Rand = vector2matrix(v_Rand, 5);
    mostrar_matriz_por_consola(Rand, "Rand");
    vector<double> b3 = {0, -14, -32.45, 20, 7.66};
    pair<vector<double>, short> x3 = Rand.EGPP(b3);
    vector<double> sol_MatLab_3 = {-0.95817, -0.58408, -1.73309, -2.02015, 1.28688};
    std::cout << std::endl << "Status: " << x3.second;
    mostrar_vector_por_consola(x3.first, "x3");
    mostrar_vector_por_consola(sol_MatLab_3, "sol_MatLab_3");
    vector<double> casi_b3 = Rand*x3.first;
    mostrar_vector_por_consola(casi_b3, "Rand*x3");
    vector<double> casi_b3_2 = Rand*sol_MatLab_3;
    mostrar_vector_por_consola(casi_b3_2, "Rand*sol_MatLab_3");
    mostrar_vector_por_consola(b3, "b3");

    std::cout << Rand;
    return 0;
}