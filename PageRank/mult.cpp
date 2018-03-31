#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <stdlib.h>
#include "VectorMapMatrix.h"
#include "rdtsc.h"

int main() {
   
	FILE * fp;
	FILE * fp2;

	fp = fopen ("mediciones.txt", "w+");
	fp2 = fopen ("mediciones2.txt", "w+");

     
	VectorMapMatrix mat1 = VectorMapMatrix(5,5);
	VectorMapMatrix mat2 = VectorMapMatrix(5,5);
	VectorMapMatrix mat3 = VectorMapMatrix(5,5);
	std::vector<float> bb(5,1.0);
	
	std::vector<vector<int> > mat4(5,vector<int>(5));
	std::vector<vector<int> > mat5(5,vector<int>(5));
	std::vector<vector<int> > mat6(5,vector<int>(5));

	for(int l=0;l<5;l++){
		for(int j=0;j<5;j++){
			mat1.asignar(l,j,20.0+l+j);
			mat2.asignar(l,j,20.0);
			mat4[l][j] = 25+j;
			mat5[l][j] = 20;
		}	
	}
	
	pair<vector<float>,short> res = mat1.EG(mat1,bb);
	
	for(int l=0;l<5;l++){
		printf("%f ",res.first[l]);
	}
	printf("%d\n",res.second);
	int acum;
	for(int h = 0; h < 100; h++){
		unsigned long start, end;
	 	RDTSC_START(start);//esto toma tiempos en mult de vector de vectores
		acum = 0;
	 	for(unsigned int i=0;i<mat4.size();i++){
			for(unsigned int j=0;j<mat5[i].size();j++){
				for(unsigned int k=0;k<mat4.size();k++){
					acum += mat4[i][k]*mat5[k][j];
				}
				mat6[i][j] = acum;
				acum = 0;
			}	
		}
		RDTSC_STOP(end);
	 	unsigned long delta = end - start;
	 	fprintf(fp,"%lu\n",delta);
		RDTSC_START(start);//esto toma tiempos en mult de nuestra implementacion de matriz
		acum = 0;
		mat3 = mat1*mat2;
	 	RDTSC_STOP(end);
	 	delta = end - start;
	 	fprintf(fp2,"%lu\n",delta);
	 		
	}


  /*  printf("10 \t 45 \n");

    Matriz A(2, 2);
    A.set(0, 0, 10);
	A.set(0, 1, 13);
	A.set(1, 0, 4);
	A.set(1, 1, 6);

	Matriz B(2, 2);
	B.set(0, 0, 3);
	B.set(0, 1, 10);
	B.set(1, 0, 1);
	B.set(1, 1, 0);


	unsigned long start, end;
	unsigned long startm, endm;
	RDTSC_START(start);
	Matriz suma = A + B;
	RDTSC_STOP(end);
	unsigned long delta = end - start;

	RDTSC_START(startm);
	Matriz multiplicacion = A * B;
	RDTSC_STOP(endm);
	unsigned long deltam = endm - startm;

	printf("el resultado de la suma (%ul): \n", delta);
	cout << suma;
	printf("\n el resultado de la multiplicación (%ul): \n", delta);
	cout << multiplicacion;*/
    return 0;
}

