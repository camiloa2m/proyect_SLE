#include <iostream>
#include "SLE.h"

using namespace std;

int main(){
	matrix A (true);
	for (int i = 0; i<A.getM(); i++){
		for (int j = 0; j<A.getN(); j++){
			cout<< A.getNum(i,j)<< " ";
		}
		cout <<endl;
	}
	double re = A.getNum(0,1) +3;
	cout << re<<endl;
	matrix I = A.ident();

	for (int i = 0; i<I.getM(); i++){
		for (int j = 0; j<I.getN(); j++){
			cout<< I.getNum(i,j)<< " ";
		}
		cout <<endl;
	}
	matrix B(3,4);

	for (int i = 0; i<(A*0.5).getM(); i++){
		for (int j = 0; j<(A*0.5).getN(); j++){
			cout<< (A*0.5).getNum(i,j)<< " ";
		}
		cout <<endl;
	}

	return 0;
}
//C:\Users\Camilo_aM\eclipse-workspace\proyectoAlgort\data.txt
