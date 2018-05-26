#include "SEL.h"
#include <cmath>

const double MARGEN_ERROR =1e-11;

matrix::matrix(){ // Construye una matriz de ceros de 3x3
	m= 3;
	n= 3;
	for (int i = 0; i<m; i++){
		std::vector<double> row;
		for (int j = 0; j<n; j++){
			if(i==j) row.push_back(1);
			else row.push_back(0);
		}
		A.push_back(row);
		row.clear(); //???
	}
}

matrix::matrix(int m, int n){ //Construye una matriz de ceros de m x n
	this->m= m;
	this->n= n;
	for (int i = 0; i<m; i++){
		std::vector<double> row;
		for (int j = 0; j<n; j++){
			row.push_back(0);
		}
		A.push_back(row);
		row.clear(); //???
	}
}

matrix::matrix(int n){ //Construye la matriz identidad de tamaño n
	this->m= n;
	this->n= n;
	for (int i = 0; i<m; i++){
		std::vector<double> row;
		for (int j = 0; j<n; j++){
			if(i==j) row.push_back(1);
			else row.push_back(0);
		}
		A.push_back(row);
		row.clear(); //???
	}
}

matrix::matrix(std::vector <std::vector<double> > mat){ //Construye una matriz que recibe un vector de vectores
	m=mat.size();
	n=mat[0].size();
	A=mat;
}

matrix::matrix(bool val){ // Construye una matriz que lee de un archivo de texto a traves de un flujo
	if (val==true){
		std::ifstream  inputFile;
		while (true) {
			std::cout  << "Ingrese direccion del archivo: "<<std::endl;
			std::string  filename;
			std::getline(std::cin , filename);
			inputFile.open(filename.c_str ());
			if (! inputFile.fail()) break;
			inputFile.clear();
			std::cerr  << "No se pudo abrir el archivo. Intente nuevamente."<< std::endl;
		}
		int k = 0;
		while (inputFile.good()){
			std::string linea;
			std::getline(inputFile, linea);
			std::string temp="";
			std::vector <double> vec;
			for (unsigned int i = 0;i<=linea.length();i++){
				if(i == linea.length()) linea[i] = '\n';///para que se tome el ultimo elemento de la linea
				if (linea[i] != ' ' && linea[i] != '\n'){
					temp+=linea[i];
				}else{
					//double num = stod(temp, nullptr);//string a double
					double num = std::atof(temp.c_str());//para linux
					vec.push_back(num);
					temp.clear();
				}
			}
			A.push_back(vec);
			k++;
		}
		A.pop_back();
		inputFile.close();
		m = A.size();//numero de filas
		n = A[0].size();//numero de columnas

		for(int i = 0; i<m;i++){
			if(A[i].size()>n) A[i].pop_back();
		}

	} else {
		std::cout<<"Ingrese numero de filas: "<<std::endl;
		std::cin >> m; // ingresa numero de filas
		std::cout<<"Ingrese numero de columnas: "<<std::endl;
		std::cin >> n; // ingresa numero de columnas
		for (int i = 0; i<m; i++){
			std::cout<<"Ingrese fila "<<i+1<<" :"<<std::endl;
			std::vector <double> row;
			for (int j = 0; j<n; j++){
				double r = 0;
				//cout<<"Ingrese elemento "<<j+1<<" :"<<endl;
				std::cin >> r;
				row.push_back(r);
			}
			A.push_back(row);
			row.clear();
			std::cout <<std::endl;
		}
	}
}


int matrix::getM(){ //Retorna numero de filas de la matriz
	return m;
}

int matrix::getN(){ //Retorna numero de columnas de la matriz
	return n;
}

void matrix::setNum(int i, int j, double val){ //Asigna un valor a la posicion (i,j) de la matriz
	A[i][j] = val;
}

double matrix::getNum(int i, int j){ //Retorna el valor en la posicion (i,j)
	return A[i][j];
}

void matrix::setN(int n){ // Redefine el numero de columnas de la matriz
	this->n=n;;
}

void matrix::setM(int m){ // Redefine el numero de filas de la matriz
	this->m=m;;
}



std::vector<double> operator+(std::vector<double> a,std::vector<double> b){ //Permite sumar un vector con otro
	std::vector<double> suma(a.size());
	for(int i=0;i<a.size();i++){
		suma[i]=b[i]+a[i];
	}
	return suma;
}

void matrix::rref(){ //Pasa la matriz a su forma escalonada reducida por renglones

	// i: filas, j: columnas
	int j=0, i;

	//El for mÃ¡s grande recorre las filas
	for(int p=0;p<m;p++){
		bool success =false;
		i=p;
		//Mientras no haya terminado de recorrer las columnas de la matriz y 'success' sea falso...
		while((j<n) && !success){
			i=p;
			//Para cada columna, recorre todas sus filas
			while(i<m){
				//Si encuentra un '0' en la columna, termina el while porque ya encontrÃ³ la columna no cero extremo izquierda
				if(A[i][j] != 0){
					success = true;
					break;
				}
				i++;
			}
			j++;
		}
		//Si encontrÃ³ la columna no cero extremo izquierda..
		if(success){
			//Si la primera fila de la columna no cero extremo izquierda tiene un 0, cÃ¡mbiela por la primera fila que no tenga un 0 en esa columna (o sea la fila i)
			if(i != p) A[p].swap(A[i]);
			//El primer elemento diferente de 0 se vuelve '1'
			MultFila(A[p], (1.0/A[p][j-1]));
			//Los elementos debajo del pivote se vuelven '0'
			for(int k=p+1;k<m;k++){
				std::vector <double> temp = A[p];
				MultFila(temp, -A[k][j-1]);
				A[k] = A[k]+ temp;
				//Esto es para corregir errores numericos
				for (int l=0;l<n;l++){
					if (std::abs(A[k][l])<= MARGEN_ERROR)
						A[k][l] = 0;
				}

			}

		}



	}

	//Ahora vuelve '0' a todos los elementos encima de los pivotes

	for(int q=m-1;q != 0; q--){
		for(int w=0;w<n;w++){
			if(std::abs(A[q][w]-1)< MARGEN_ERROR){
				A[q][w]=1;
				for(int k=q-1; k!=-1;k--){
					std::vector <double>temp= A[q];
					MultFila(temp,-A[k][w]);
					A[k] = A[k]+temp;
				}
			}
		}
	}
}

std::vector< std::vector<double> > matrix::Menor(std::vector< std::vector<double> > mat ,int i, int j){ //Retorna el Menor(i,j) de una matriz
	std::vector< std::vector<double> > menor;
	for(int l=0;l < mat.size();l++){
		std::vector <double> filatemp;
		for(int p=0;p < mat[0].size();p++){
			if (p != j) filatemp.push_back(mat[l][p]);
		}
		if(l != i) menor.push_back(filatemp);
	}
	return menor;

}




double matrix::det(std::vector< std::vector<double> > mat){ //Calcula recursivamente el determinante de una matriz, a traves del metodo por cofactores. El caso base es el de una matriz 2 x 2
	double suma = 0;
	int m=mat.size();
	int n=mat[0].size();

	if (m==n) {
		if(m==2) return mat[0][0]*mat[1][1]-mat[1][0]*mat[0][1];
		for(int j=0; j < n;j++){
			suma += mat[0][j]*pow(-1,j)*det(Menor(mat,0,j));
		}
		return suma;
	} else {
		throw std::underflow_error("La matriz no es cuadrada!!");

	}

}
double matrix::det(){
	return det(A);
}


bool matrix::isInvertible(){
	return !det(A)==0;
}



void matrix::MultFila(std::vector<double> &vec, double escalar){ //Multiplica un vector por un escalar
	for(int i=0;i<vec.size();i++){
		vec[i] *= escalar;
	}
}



matrix matrix::Concat(matrix mat){//Concatena dos matrices
	std::vector <std::vector<double> > tmp=A;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			tmp[i].push_back(mat.getNum(i,j));
		}
	}
	matrix conc(tmp);
	return conc;
}

matrix matrix::inverse(){ //Retorna la inversa de la matriz
	if(det(A) != 0){
		std::vector< std::vector<double> > inv;
		matrix mat(A);
		matrix ident(n);
		matrix mataum = mat.Concat(ident); //Concatena la matriz con la identidad n y realizada eliminacion gaussiana. Si la inversa existe, es la matriz que queda a la derecha.
		mataum.rref();
		for(int i=0;i<mataum.getM();i++){
			std::vector <double> temp;
			for(int j=mataum.getM();j<mataum.getN();j++){
				temp.push_back(mataum.getNum(i, j));
			}
			inv.push_back(temp);
		}
		matrix inver(inv);
		return inver;
	}
	throw std::underflow_error("La matriz no es invertible!!");
}

int matrix::rank(){ //Rango de una matriz
	this->rref();
	int count =0;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			if (this->getNum(i,j)==1) count++;
			break;
		}
	}
	return count;
}


std::vector<double> matrix::SolvGaussJordan(){ //Calcula la (una) solucion del sistema a traves del metodo de Gauss-Jordam
	this->rref(); //Pasa la matriz a su FERR
	matrix mat(A); //mat es la matriz aumentada del sistema
	std::vector<double> sol1(n-1);
	matrix mat2(m,n-1); //mat2 es la matriz de coeficientes
	for(int i=0;i<m;i++){
		for(int j=0;j<n-1;j++){
			mat2.setNum(i, j, mat.getNum(i, j)); //Aca se llena mat2 quitandole la ultima columna a mat, que es el vector columna b de la ecuacion Ax=b
		}
	}
	if(mat.rank() > mat2.rank()) { //Si el rango de la aumentada es mayor que el de la de coeficientes...
		std::cout << "El sistema no tiene solucion!"<<std::endl<<std::endl;

	}
	if((mat.rank() <= mat2.rank()) && (mat2.rank() < mat2.getN())){
		std::cout << "El sistema tiene infinitas soluciones!"<<std::endl<<std::endl;
		struct pareja{ //Estructura para guardar la posicion (i,j) de las variables pivote
			int i;
			int j;
		};
		std::vector<pareja> varpiv; //Vector de variables pivote
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				if(mat.getNum(i,j)==1){
					pareja par;
					par.i=i;
					par.j=j;
					varpiv.push_back(par);
					break;
				}
			}
		}
		pareja ult_col;
		ult_col.i=0;
		ult_col.j=n-1;
		varpiv.push_back(ult_col);

		for(int i=0;i<sol1.size();i++){
			sol1[i]=0; //Llena el vector solucion de ceros
		}
		for(int i=0;i<m;i++){
			if(i==varpiv[i].j){ //Cambia el valor de las variables pivote
				sol1[i]=A[varpiv[i].i][n-1];
			}
		}


	}
	if((mat.rank() <= mat2.rank()) and (mat2.rank() == mat2.getN())){
		std::cout << "El sistema tiene una unica solucion!"<<std::endl<<std::endl;
		for(int i=0;i<n-1;i++){
			sol1[i]=mat.getNum(i, n-1);
		}
	}
	//std::cout<< "Norma 1: " << std::abs(mat2*sol1()-)

	return sol1; //Retorna el vector solucion


}

void matrix::printVector(std::vector<double> vec){
	for(int i=0;i<vec.size();i++){
		std::cout<<vec[i]<<" ";
	}
	std::cout<<std::endl;
}

matrix matrix::transpose(){ //Retorna la matriz transpuesta
	matrix trans (n,m);
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			trans.setNum(i, j, this->getNum(j, i));
		}
	}
	return trans;
}


std::vector<matrix> matrix::factLU(){//metodo dollitle
	if(m==n){
		matrix U (n,n);//matriz 0 de tamaÃƒÂ±o n*n // sera matriz triangular superior
		matrix L (n);//matriz identidad de tamaÃƒÂ±o n*n  // // sera matriz triangular inferior
		matrix mat(A);
		for(int k = 0; k<n; k++){
			U.setNum(k,k,mat.getNum(k, k));
			for (int i = k+1; i<n ; i++){
				L.setNum(i,k,mat.getNum(i,k)/mat.getNum(k, k));//pivote divide elementos de columna respectiva
				U.setNum(k,i,mat.getNum(k,i));//fila al lado del pivote permanece igual
			}
			for(int i= k+1; i<n; i++){
				for(int j = k+1; j <n; j++){
					mat.setNum(i,j,mat.getNum(i,j) - L.getNum(i,k)*U.getNum(k,j));
				}
			}
		}
		std::vector<matrix> rta;
		rta.push_back(L);
		rta.push_back(U);
		return rta;
	}
	throw std::underflow_error("La matriz no es cuadrada!!");
}

std::vector<double> matrix::solwithLU(){
	//solucion ecuacion Ax = LUx = b // Tomar Ux = y
	//Resolver Ly = b; por sustitucion hacia abajo, Se halla y
	// Una vez hallados los valores de y:
	//resolver Ux=y, por sustitucion hacia atras
	if(m+1==n){
		std::vector<double> b;
		for(int i = 0; i<m;i++){
			b.push_back(A[i][n-1]);
		}

		std::vector<std::vector<double>> A2 = A;

		for(int i = 0; i<m;i++){
			A2[i].pop_back();
		}

		int q = A2[0].size();
		matrix B(A2);
		std::vector<matrix> rta = B.factLU();
		rta[0];// Matrix L;
		rta[1];// Matrix U;


		std::vector<double> y(b.size());
		for (int i=0; i<q; i++) {// sustitucion hacia abajo
			y[i] = b[i];
			for (int j= 0 ;j<i; j++) {
				y[i] = y[i]-rta[0].getNum(i,j)*y[j];
			}
		}

		std::vector<double> x(b.size());
		for (int i=q-1; i>=0; i--) {//Sustitucion hacia abajo
			x[i] = y[i];
			for (int j=i+1;j<q; j++) {
				x[i] = x[i]- rta[1].getNum(i,j)*x[j];
			}
			x[i]= x[i]/rta[1].getNum(i,i);
		}

		return x;
	}
	//throw std::underflow_error("La matriz de coeficientes no es cuadrada!!");
}

matrix & matrix::operator=(matrix & a){ //Define una matriz a traves de la igualdad
	if(a.getM() == this->m && a.getN()== this->n){
		for (int i = 0; i<m; i++){
			for (int j = 0; j<n; j++){
				this->A[i][j] = a.getNum(i,j);
			}
		}
		return *this;
	}
	throw std::underflow_error("Las matrices no son del mismo tamaÃ±o");
}

bool matrix::operator==(matrix a){ //Compara dos matrices y dice si son iguales
	if(a.getM() == m && a.getN()== n){
		for (int i = 0; i<m; i++){
			for (int j = 0; j<n; j++){
				if(A[i][j] != a.getNum(i,j)) return false;
			}
		}
		return true;
	}
	throw std::underflow_error("Las matrices son diferentes en tamaÃ±o");
}

bool matrix::operator!=(matrix a){ //Compara dos matrices y dice si son diferentes
	if(a.getM() == m && a.getN()== n){
		for (int i = 0; i<m; i++){
			for (int j = 0; j<n; j++){
				if(A[i][j] != a.getNum(i,j)) return true;
			}
		}
		return false;
	}
	throw std::underflow_error("Las matrices son diferentes en tamaÃ±o");
}


matrix matrix::operator+(matrix a){ //Suma dos matrices del mismo tamaño
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
	throw std::underflow_error("Las matrices no se pueden sumar");
}
matrix matrix::operator-(matrix a){ //Resta dos matrices
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
	throw std::underflow_error("Las matrices no se pueden restar");
}
matrix matrix::operator*(double a){ //Multiplica una matriz por un escalar
	matrix B(m,n);
	for (int i = 0; i<m; i++){
		for (int j = 0; j<n; j++){
			B.setNum(i,j,A[i][j]*a);
		}
	}
	return B;
}
matrix matrix::operator*(matrix a){
	if(n == a.getM()){
		std::vector <std::vector<double> > mult(m);
		for(int i = 0; i < m; ++i){
				for(int j = 0; j < a.getN(); ++j){
					for(int k=0; k<n; ++k){
						mult[i][j] += this->getNum(i,k) * a.getNum(k,j);
					}
				}
			}

		matrix B(mult);
		return B;
	}
	throw std::underflow_error("Las matrices no se pueden multiplicar");
}



