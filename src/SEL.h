#ifndef SLE_H_
#define SLE_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

class matrix{
private:
	std::vector< std::vector<double> > A;
	int m;
	int n;

	void MultFila(std::vector<double> &vec, double escalar); // Multiplica un vector por un escalar
	double det(std::vector< std::vector<double> > mat);
	void printVector(std::vector<double> vec);





public:
	matrix(); //matriz identidad de tamaÃ±o 3*3
	matrix(int n); //matriz identidad de tamaÃ±o n*n
	matrix(int m, int n); //matriz 0 de tamaÃ±o n*n
	matrix(std::vector <std::vector<double> > mat);
	matrix(bool val); //matriz a partir de: si se quiere leer archivo true; false si se ingresa desde consola
	int getM(); //da el numero de filas
	int getN(); //da el numero de columnas
	void setM(int n);
	void setN(int n);
	double getNum(int i, int j); //da el numero en la posicion ij
	void setNum(int i, int j, double val); //cambia el numero en la posicion ij
	bool isInvertible();
	int rank();//rango de la matriz

	std::vector< std::vector<double> > Menor(std::vector< std::vector<double> > mat  ,int i, int j); //Retorna la matriz menor (i,j)
	double det(); //determinate de la matriz

	matrix inverse(); //da la matriz inversa
	matrix transpose(); //da la matriz transpuesta
	matrix Concat(matrix mat); //concatena con una matriz
	matrix concatenate(std::vector<double> C); //concatena con un vector
	void rref(); // da la matriz escalonada reducida por reglones
	std::vector<double> solwithInverse();
	std::vector<double>SolvGaussJordan();// muestra todas las soluciones
	std::vector<double> solwithLU();
	std::vector<matrix> factLU();//factoriza en matriz L (Lower) y matriz U(upper) matrices triangulares



	matrix & operator=(matrix & a);
	matrix operator+(matrix a);
	matrix operator-(matrix a);
	matrix operator*(double a);
	matrix operator*(matrix a);
	bool operator==(matrix a);
	bool operator!=(matrix a);

	//double operator [](int i, int j);

};



#endif /* SLE_H_ */
