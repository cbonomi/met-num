#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <stdlib.h>
#include <chrono>
#include "VectorMapMatrix.h"
#include "rdtsc.h"

int main(){
    VectorMapMatrix A(8756,3387);
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
    C= I*R;
///Prueba básica de multiplicación
    VectorMapMatrix M1(1000,1500);
    VectorMapMatrix M2(1500,1200);
    M1.asignar(120, 30, 3.4);
    M2.asignar(30, 500, 2.0);
    M1.asignar(420, 600, 4.5);
    M2.asignar(600, 500, 2.0);
    M1.asignar(420, 700, 9.0);
    M2.asignar(700, 500, -1.0);
    auto t1 = std::chrono::system_clock::now();
    VectorMapMatrix Res1 = M1*M2;
    auto t2 = std::chrono::system_clock::now();
    auto t3 = std::chrono::system_clock::now();
    VectorMapMatrix Res2 = M1.mult(M2);
    auto t4 = std::chrono::system_clock::now();
    std::cout << "El tiempo del oper* dividido el tiempo de la funcion mult es: " << (t2-t1)/(t4-t3) << std::endl;
    std::cout << "Res_(120,500) debe ser 6.8 y dio respectivamente: " << Res1.at(120, 500) << " , " << Res2.at(120, 500) << std::endl;
    std::cout << "Res_(420,500) debe ser 0.0 y dio respectivamente: " << Res1.at(420, 500) << " , " << Res2.at(420, 500) << std::endl;
///Prueba más completa
    VectorMapMatrix M(3, 4);
    VectorMapMatrix N(4, 3);
    vector<double> v_M = {1, 3, 5, 6, -0.4, -8.4, 5.9, 16.002, 23, 0.228, 0.003, 7};
    vector<double> v_N = {-0.04, -9.31, -6.77, 4.5, 12.43, 9.04, -8.53, 0.04, -0.73, 6.4, 7.53, -7.89};
    for(uint i = 0; i < 12; ++i){
        M.asignar(i/4, i%4, v_M[i]);
        N.asignar(i/3, i%3, v_N[i]);
    }/*
    M = |   1,     3,     5,      6|            N = |-0.04, -9.31, -6.77|
        |-0.4,  -8.4,   5.9, 16.002|                |  4.5, 12.43,  9.04|
        |  23, 0.228, 0.003,      7|                |-8.53,  0.04, -0.73|
                                                    |  6.4,  7.53, -7.89|
    */
    VectorMapMatrix R1 = M.mult(N);
    VectorMapMatrix R2 = N.mult(M);
    /*Según Octave las soluciones son:
     * R1 =    | 9.2100,    73.3600,   -30.6400|            R2 =   |-152.026,    76.540,   -55.149,  -196.609|
               |14.3018,    20.0431,  -203.7908|                   | 207.448,   -88.851,    95.864,   289.185|
               |44.8804,  -158.5858,  -208.8811|                   | -25.336,   -26.092,   -42.416,   -55.650|
                                                                   |-178.082,   -45.851,    76.403,   103.665|
     */
    std::cout << std::endl << "M =  |";
    for(uint i = 0; i < 12; ++i){
        std::cout << M.at(i/4, i%4);
        if(i%4 < 3)
            std::cout << ",  ";
        else {
            std::cout << "|" << std::endl;
            if(i != 11){
                std::cout << "      |";
            }
        }
    }
    std::cout << std::endl << "N =  |";
    for(uint i = 0; i < 12; ++i){
        std::cout << N.at(i/3, i%3);
        if(i%3 < 2)
            std::cout << ",  ";
        else {
            std::cout << "|" << std::endl;
            if(i != 11){
                std::cout << "      |";
            }
        }
    }
    std::cout << std::endl << "R1 =  |";
    for(uint i = 0; i < 9; ++i){
        std::cout << R1.at(i/3, i%3);
        if(i%3 < 2)
            std::cout << ",  ";
        else {
            std::cout << "|" << std::endl;
            if(i != 8){
                std::cout << "      |";
            }
        }
    }
    std::cout << std::endl << "R2 =  |";
    for(uint i = 0; i < 16; ++i){
        std::cout << R2.at(i/4, i%4);
        if(i%4 < 3)
            std::cout << ",  ";
        else {
            std::cout << "|" << std::endl;
            if(i != 15){
                std::cout << "      |";
            }
        }
    }
    return 0;
}