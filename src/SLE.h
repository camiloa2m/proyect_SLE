#ifndef SLE_H_
#define SLE_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class matrix{
private:
	std::vector<std::vector<double>> A;
	int m;
	int n;
public:
	matrix(); //matriz identidad de tamaño 3*3
	matrix(int n); //matriz identidad de tamaño n*n
	matrix(int m, int n); //matriz 0 de tamaño n*n
	~matrix();

	matrix(bool val); //matriz apartir de: si se quiere leer archivo true; false si se ingresa desde consola

	int getM(); //da el numero de filas
	int getN(); //da el numero de columnas
	double getNum(int i, int j); //da el numero en la posicion ij
	void setNum(int i, int j, double val); //cambia el numero en la posicion ij

	int rank();//rango de la matriz
	double det(); //determinate de la matriz
	matrix ident(); //Matriz identidad asociada
	matrix inverse(); //da la matriz inversa
	matrix transpose(); //da la matriz transpuesta
	matrix concatenate(std::vector<std::vector<double>> C); //concatena con una matriz
	matrix concatenate(std::vector<double> C); //concatena con un vector
	matrix rref(); // da la matriz escalonada reducida por reglones


	std::vector<double> solwithInverse();
	std::vector<std::vector<double>> solGaussJordan();// muestra todas las soluciones
	factLU();//
	iter_Richardson()//Metodo de Richardson
	iter_Jacobi()//Metodo de Jacobi
	iter_GaussSeidel//Metodo de Gauss-Seidel

	matrix & operator=(matrix & a);
	matrix operator+(matrix a);
	matrix operator-(matrix a);
	matrix operator*(double a);
	matrix operator*(matrix a);

};



#endif /* SLE_H_ */
