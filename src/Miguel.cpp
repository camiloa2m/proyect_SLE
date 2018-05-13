#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void MultFila(vector<double> &vec, double escalar);
vector<double> operator+(vector<double> vec, vector<double> vec2);
void GaussJordan(vector <vector <double> > &matrix);


int main(){
	vector <vector<double> > matrix = {{-0,1,-3,-25}, {0,24,-20,13},{0,-22,23,15}};
	vector<double> b = {1,2,3};

	//imprime la matriz
	for(int i=0;i<matrix.size();i++){
		for(int j=0;j<matrix[0].size();j++){
			cout << matrix[i][j]<<" ";
		}
		cout <<endl;
	}
	cout << "-------------------"<<endl;

	//Aplica Gauss-Jordan a la matriz (la cambia por referencia)
	GaussJordan(matrix);

	//Imprime la forma escalonada reducida por renglones de la matriz
	for(int i=0;i<matrix.size();i++){
		for(int j=0;j<matrix[0].size();j++){
			cout << matrix[i][j]<<" ";
		}
		cout <<endl;
	}
	cout << "-------------------"<<endl;
	return 0;
}

//Método para multiplicar una fila de la matriz por un escalar
void MultFila(vector<double> &vec, double escalar){
	for(int i=0;i<vec.size();i++){
		vec[i] *= escalar;
	}
}

//Método para sumar dos filas de la matriz
vector<double> operator+(vector<double> vec, vector<double> vec2){
	vector<double> suma(vec.size());
	for(int i=0;i<vec.size();i++){
		suma[i]=vec2[i]+vec[i];
	}
	return suma;
}

void GaussJordan(vector <vector <double> > &matrix){
	// i: filas, j: columnas
	int j=0, i;

	//El for más grande recorre las filas
	for(int p=0;p<matrix.size();p++){
		bool success =false;
		i=p;
		//Mientras no haya terminado de recorrer las columnas de la matriz y 'success' sea falso...
		while((j<matrix[0].size()) && !success){
			i=p;
			//Para cada columna, recorre todas sus filas
			while(i<matrix.size()){
				//Si encuentra un '0' en la columna, termina el while porque ya encontró la columna no cero extremo izquierda
				if(matrix[i][j] != 0){
					success = true;
					break;
				}
				i++;
			}
			j++;
		}
		//Si encontró la columna no cero extremo izquierda..
		if(success){
			//Si la primera fila de la columna no cero extremo izquierda tiene un 0, cámbiela por la primera fila que no tenga un 0 en esa columna (o sea la fila i)
			if(i != p) matrix[p].swap(matrix[i]);
			//El primer elemento diferente de 0 se vuelve '1'
			MultFila(matrix[p], (1.0/matrix[p][j-1]));
			//Los elementos debajo del pivote se vuelven '0'
			for(int k=p+1;k<matrix.size();k++){
				vector <double> temp = matrix[p];
				MultFila(temp, -matrix[k][j-1]);
				matrix[k] = matrix[k]+ temp;

				//Esto es porque a veces sale 1e-15 en vez de 0
				for (int l=0;l<matrix[0].size();l++){
					if (abs(matrix[k][l])<= 1e-11)
						matrix[k][l] = 0;
				}

			}

		}


	}

	//Ahora vuelve '0' a todos los elementos encima de los pivotes

	for(int q=matrix.size()-1;q != 0; q--){
		for(int w=0;w<matrix[0].size();w++){
			if(abs(matrix[q][w]-1)< 1e-10){
				matrix[q][w]=1;
				for(int k=q-1; k!=-1;k--){
					vector <double>temp= matrix[q];
					MultFila(temp,-matrix[k][w]);
					matrix[k] = matrix[k]+temp;
				}
			}
		}
	}





}
