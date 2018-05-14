#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void MultFila(vector<double> &vec, double escalar);
vector<double> operator+(vector<double> vec, vector<double> vec2);
void GaussJordan(vector <vector <double> > &mat);
vector <vector<double> > Menor(vector<vector <double> > mat, int i, int j);
double det(vector <vector<double> > mat);
bool isInvertible(vector <vector<double> > mat);
vector <vector<double> > Ident(int n);
vector <vector<double> > Concat(vector <vector<double> > mat1, vector <vector<double> > mat2);
vector <vector<double> > Inverse(vector <vector<double> >mat);
int Rank(vector <vector<double> > mat);

int main(){
	vector <vector<double> > matrix = {{1,2,-1},{-4,8,-6},{-3,3,6}};


	//imprime la matriz
	for(int i=0;i<matrix.size();i++){
		for(int j=0;j<matrix[0].size();j++){
			cout << matrix[i][j]<<" ";
		}
		cout <<endl;
	}
	cout << "-------------------"<<endl;
	cout << "Determinante de la matriz: "<< det(matrix) <<endl;
	cout <<endl;

	//matriz identidad de 2x2
	vector <vector<double> > ident = Ident(matrix.size());

	//Concatena la matriz 'matrix' con su matriz identidad
	vector <vector<double> > aument = Concat(matrix,ident);

	//Calcula la matriz inversa de 'matrix'
	vector <vector<double> > inv = Inverse(matrix);

	cout << "Inversa de la matriz: "<<endl<<endl;

	//Imprime la matriz inversa
	for(int i=0;i<matrix.size();i++){
		for(int j=0;j<matrix[0].size();j++){
			cout << inv[i][j]<<" ";
		}
		cout <<endl;
	}
	cout << "-------------------"<<endl;


	//Aplica Gauss-Jordan a la matriz (la cambia por referencia)
	GaussJordan(matrix);


	//Imprime la forma escalonada reducida por renglones de la matriz

	cout << "Forma escalonada reducida por renglones de la matriz: "<<endl<<endl;
	for(int i=0;i<matrix.size();i++){
		for(int j=0;j<matrix[0].size();j++){
			cout << matrix[i][j]<<" ";
		}
		cout <<endl;
	}
	cout << "-------------------"<<endl;

	cout << "Rango de la matriz: " << Rank(matrix)<<endl;

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

vector <vector<double> > Menor(vector<vector <double> > mat ,int i, int j){
	vector <vector<double> > menor;

	for(int l=0;l < mat.size();l++){
		vector <double> filatemp;
		for(int p=0;p < mat[0].size();p++){
			if (p != j) filatemp.push_back(mat[l][p]);
		}
		if(l != i) menor.push_back(filatemp);
	}
	return menor;
}

double det(vector <vector<double> > mat){
	double suma = 0;
	int m=mat.size();
	int n=mat[0].size();

	if(m==n){
		if(m==2) return mat[0][0]*mat[1][1]-mat[1][0]*mat[0][1];
		for(int j=0; j < n;j++){
			suma += mat[0][j]*pow(-1,j)*det(Menor(mat,0,j));
		}
		return suma;
	}else{
		cerr << "La matriz no es cuadrada!!"<<endl;

	}
}

bool isInvertible(vector <vector<double> > mat){
	return !det(mat)==0;
}

vector <vector<double> > Ident(int n){
	vector <vector<double> > ident;
	for(int i=0;i<n;i++){
		vector <double> filatemp;
		for(int j=0;j<n;j++){
			if(i==j){
				filatemp.push_back(1);
			}else{
				filatemp.push_back(0);
			}
		}
		ident.push_back(filatemp);
	}

	return ident;
}

vector <vector<double> > Concat(vector <vector<double> > mat1, vector <vector<double> > mat2){
	int m=mat1.size(), n=mat1[0].size();
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			mat1[i].push_back(mat2[i][j]);
		}
	}
	return mat1;

}

vector <vector<double> > Inverse(vector <vector<double> >mat){
	if(det(mat) != 0){
		int n= mat.size();
		vector <vector<double> >inv;
		vector <vector<double> > mataum = Concat(mat,Ident(n));
		GaussJordan(mataum);
		for(int i=0;i<mataum.size();i++){
			vector <double> temp;
			for(int j=mataum.size();j<mataum[0].size();j++){
				temp.push_back(mataum[i][j]);
			}
			inv.push_back(temp);
		}
		return inv;
	}
	cerr << "La matriz no es invertible!!"<<endl;
}

int Rank(vector <vector<double> > mat){
	int rango = 1, m=mat.size(), n=mat[0].size();
	for(int i=1; i < m;i++){
		for(int j=1;j < n;j++){
			if(mat[i][j]==1 and mat[i-1][j]==0) rango++;
		}
	}
	return rango;
}







