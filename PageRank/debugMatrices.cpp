#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <stdlib.h>
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
    return 0;
}