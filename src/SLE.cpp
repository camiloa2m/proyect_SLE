#include "SLE.h"
#include <iostream>
#include <vector>
using namespace std;

matrix::matrix(){
	m= 3;
	n= 3;
	for (int i = 0; i<m; i++){
		for (int j = 0; j<n; j++){
			if(i==j) A[i][j]=1;
			else A[i][j]=0;
		}
	}
}
/*matrix::matrix(double w[][]){
	for (int i = 0; i<sizeof(w)/sizeof(*w); i++){
		for (int j = 0; j<sizeof(w)/sizeof(w[0][0]); j++){
			A[i][j]= w[i][j];
		}
		cout << endl;
	}
	m = A.size();//numero de filas
	n = A[0].size();//numero de columnas
}*/
matrix::matrix(int z){
	m= z;
	n= z;
	for (int i = 0; i<m; i++){
		for (int j = 0; j<n; j++){
			if(i==j) A[i][j]=1;
			else A[i][j]=0;
		}
	}
}

vector<vector<double>> matrix::ident(){
	for (int i = 0; i<n; i++){
		for (int j = 0; j<n; j++){
			if(i==j) A[i][j]=1;
			else A[i][j]=0;
		}
	}
	return A;
}

vector<vector<double>> matrix::rref(){
	int min= m <= n? m : n;
	//hace ceros bajo el pivote en todas las columnas que lo permiten
	for(int k = 0;k<min ;++k){//k = menor numero entre filas y columnas
		int ceros= 0;
		for(int i = k;i<m ;++i){//filas//verifica si la columna es de ceros
			if (A[i][k]!=0){
				swap(A[k],A[i]);
				break;
			} else {
				ceros++;
			}
		}
		double t= A[k][k];
		for(int j = k;j<n;++j){//Columnas
			A[k][j] *= 1/t;//hace pivote 1 la fila cambia de valores
		}
		for(int i = k+1;i<m ;++i){//filas
			if(ceros == m) break; // salta si la columna es de ceros
			double temp= A[i][k];
			for(int j = k;j<n;++j){//Columnas
				A[i][j] = A[i][j]-(temp*A[k][j]);//se hacen toda la columna bajo el pivote cero
			}
		}
	}

	//hace ceros SOBRE el pivote en todas las columnas que lo permiten
	for(int k = 0;k<min ;++k){//k = menor numero entre filas y columnas
		int cer = 0;
		int pos = 0;//posicion del 1 en columna j
		for(int j = 0;j<n;++j){//Columnas
			if(A[k][j]!=1){
				cer++;
			}else{
				pos = j;//posicion del 1 en columna j
				break;
			}
		}
		for(int i = 0;i<k ;++i){//filas
			if (cer == n) break; // salta si la columna es de ceros// falta agregar que la envie al final
			double temp= A[i][pos];
			for(int j = pos;j<n;++j){//Columnas
				A[i][j] = A[i][j]-(temp*A[k][j]);//se hacen toda la columna sobre el pivote cero
			}
		}
	}
	return A;
}
