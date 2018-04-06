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
    return 0;
}