#include <iostream>
#include <vector>
#include <string>
#include "SLE.h"
using namespace std;
vector<vector<double>> ferr(vector<vector<double>> A);

int main(){
	string ecu={1,3,-5,1,4,2,5,-2,4,6};
	int m = 2;//numero de filas
	int n = 5;//numero de columnas
	double** A = new double*[m];
	for(int i = 0; i < m; ++i)
	    A[i] = new double[n];
	for (int i = 0; i<m; i++){
		for (int j = 0; j<n; j++){
			A[i][j]=f[j];
		}
	}


	//imprime matriz original
	for (int i = 0; i<m; i++){
		for (int j = 0; j<n; j++){
			cout << "  "<< A[i][j]<<"  ";
		}
		cout << endl;
	}


	cout << endl;

}

vector<vector<double>> ferr(vector<vector<double>> A){
	int m = A.size();//numero de filas
	int n = A[0].size();//numero de columnas
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
