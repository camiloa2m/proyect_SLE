/*
 * SLE.h
 *
 *  Created on: 12/05/2018
 *      Author: Camilo_aM
 */

#ifndef SLE_H_
#define SLE_H_

#include<vector>

class matrix{
private:
	std::vector<std::vector<double>> A;
	int m;
	int n;
public:
	matrix();
	matrix(double **h);
	matrix(int z);
	int rank();
	std::vector<std::vector<double>> ident(); //Matriz identidad asociada
	std::vector<std::vector<double>> inverse();
	std::vector<std::vector<double>> concatenate(std::vector<std::vector<double>> C);
	std::vector<std::vector<double>> rref();

	std::vector<std::vector<double>> solwithInverse();
	std::vector<std::vector<double>> solGaussJordan();

};



#endif /* SLE_H_ */
