#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <stdlib.h>
#include "Matriz.h"
#include "rdtsc.h"

int main() {
   
	FILE * fp;
	FILE * fp2;

	fp = fopen ("mediciones.txt", "w+");
	fp2 = fopen ("mediciones2.txt", "w+");

     
	Matriz mat = Matriz(5,5);
	Matriz mat2 = Matriz(5,5);
	Matriz mat3 = Matriz(5,5);

	std::vector<vector<int> > mat4(5,vector<int>(5));
	std::vector<vector<int> > mat5(5,vector<int>(5));
	std::vector<vector<int> > mat6(5,vector<int>(5));

	for(int l=0;l<5;l++){
		for(int j=0;j<5;j++){
			mat.set(l,j,25+j);
			mat2.set(l,j,20);
			mat4[l][j] = 25+j;
			mat5[l][j] = 20;
		}	
	}
	int acum;
	for(int h = 0; h < 100; h++){
		unsigned long start, end;
	 	RDTSC_START(start);
		acum = 0;
	 	for(int i=0;i<5;i++){
			for(int j=0;j<5;j++){
				for(int k=0;k<5;k++){
					acum += mat.get(i,k)*mat2.get(k,j); 
				}
				mat3.set(i,j,acum);
				acum = 0;
			}	
		}
		RDTSC_STOP(end);
	 	unsigned long delta = end - start;
	 	fprintf(fp,"%lu\n",delta);
		RDTSC_START(start);
		acum = 0;
		for(int i=0;i<mat4.size();i++){
			for(int j=0;j<mat5[i].size();j++){
				for(int k=0;k<mat4.size();k++){
					acum += mat4[i][k]*mat5[k][j];
					}
				mat6[i][j] = acum;
				acum = 0;
			}	
		}
	 	RDTSC_STOP(end);
	 	delta = end - start;
	 	fprintf(fp2,"%lu\n",delta);
	 		
	}
	printf("%u\n",mat4[0][1]);
	printf("%u\n",mat.get(0,1));
	/*mat.~Matriz();
	mat2.~Matriz();
	mat3.~Matriz();*/
	

    return 0;
}

