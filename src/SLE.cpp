#include "SLE.h"

using namespace std;

matrix::matrix(){
	m= 3;
	n= 3;
	for (int i = 0; i<m; i++){
		vector<double> row;
		for (int j = 0; j<n; j++){
			if(i==j) row.push_back(1);
			else row.push_back(0);
		}
		A.push_back(row);
		row.clear();
	}
}

matrix::matrix(int m, int n){
	this->m= m;
	this->n= n;
	for (int i = 0; i<m; i++){
		vector<double> row;
		for (int j = 0; j<n; j++){
			row.push_back(0);
		}
		A.push_back(row);
		row.clear();
	}
}

matrix::matrix(int n){
	this->m= n;
	this->n= n;
	for (int i = 0; i<m; i++){
		vector<double> row;
		for (int j = 0; j<n; j++){
			if(i==j) row.push_back(1);
			else row.push_back(0);
		}
		A.push_back(row);
		row.clear();
	}
}

matrix::~matrix(){
}


matrix::matrix(bool val){
	if (val == true){
		//vector<vector<double>> A;
		ifstream  inputFile;
		while (true) {
			cout  << "Ingrese direccion del archivo: "<<endl;
			string  filename;
			getline(cin , filename);
			inputFile.open(filename.c_str ());
			if (! inputFile.fail()) break;
			inputFile.clear();
			cerr  << "No se pudo abrir el archivo. Intente nuevamente."<< endl;
		}
		int k = 0;
		while (inputFile.good()){
			string linea;
			getline(inputFile, linea);
			string temp="";
			vector <double> vec;
			for (unsigned int i = 0;i<=linea.length();++i){
				if(i == linea.length()) linea[i]= '\n';///para que se tome el ultimo elemento de la linea
				if (linea[i] != ' ' && linea[i] != '\n'){
					temp+=linea[i];
				}else{
					double num = stod(temp);//string a double
					vec.push_back(num);
					temp.clear();
				}
			}
			A.push_back(vec);
			k++;
		}
		inputFile.close();
		m = A.size();//numero de filas
		n = A[0].size();//numero de columnas

	} else {
		cout<<"Ingrese numero de filas: "<<endl;
		cin >> m; // ingresa numero de filas
		cout<<"Ingrese numero de columnas: "<<endl;
		cin >> n; // ingresa numero de columnas
		for (int i = 0; i<m; i++){
			cout<<"Ingrese fila "<<i+1<<" :"<<endl;
			vector <double> row;
			for (int j = 0; j<n; j++){
				double r = 0;
				cout<<"Ingrese elemento "<<j+1<<" :"<<endl;
				cin >> r;
				row.push_back(r);
			}
			A.push_back(row);
			row.clear();
			cout <<endl;
		}
	}
}

int matrix::getM(){
	return m;
}
int matrix::getN(){
	return n;
}
double matrix::getNum(int i, int j){
	return A[i][j];
}
void matrix::setNum(int i, int j, double val){
	A[i][j] = val;
}


matrix matrix::ident(){
	matrix B (n);
	return B;
}



martrix matrix::rref(){// falta arreglarlo para clase matrix
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

/*
matrix & matrix::operator=(matrix & a){
	if(a.getM() == this->m && a.getN()== this->n){
		for (int i = 0; i<m; i++){
			for (int j = 0; j<n; j++){
				this->A[i][j] = a.getNum(i,j);
			}
		}
		return *this;
	} else {
		cerr << "No son del mismo tamaño";
	}
}*/
matrix matrix::operator+(matrix a){
	if(a.getM() == m && a.getN()== n){
		matrix B(a.getM(),a.getN());
		for (int i = 0; i<m; i++){
			for (int j = 0; j<n; j++){
				double k = A[i][j]+a.getNum(i,j);
				B.setNum(i,j,k);
			}
		}
		return B;
	}
	cerr << "No se pueden sumar";
}
matrix matrix::operator-(matrix a){
	if(a.getM() == m && a.getN()== n){
		matrix B(a.getM(),a.getN());
		for (int i = 0; i<m; i++){
			for (int j = 0; j<n; j++){
				double k = A[i][j]-a.getNum(i,j);
				B.setNum(i,j,k);
			}
		}
		return B;
	}
	cerr << "No se pueden restar";
}
matrix matrix::operator*(double a){
	matrix B(m,n);
	for (int i = 0; i<m; i++){
		for (int j = 0; j<n; j++){
			double k = A[i][j]*a;
			B.setNum(i,j,k);
		}
	}
	return B;
}
matrix matrix::operator*(matrix a){//-->>> falta hacerlo
	if(n == a.getM()){
		matrix B(m,a.getN());
		/*for (int i = 0; i<n; i++){
			for (int j = 0; j<n; j++){
				double k = A[i][j]-a.getNum(i,j);
				B.setNum(i,j,k);
			}
		}*/
		return B;
	}
	cerr << "No se pueden multiplicar";
}

