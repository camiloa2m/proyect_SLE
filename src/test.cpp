#include "SEL.h"
using namespace std;

int main(){
	std::vector<std::vector<double> > mat={{2, 3}, {6,7}};
	std::vector<std::vector<double> > mat2={{7, 8}, {-1,3}};
	//matrix p (true);
	matrix h(mat);
	//matrix k(mat2);
	//matrix mult = h*k;
	// /home/vonnewmann/Documentos/Proyecto/data/LeerMatriz
	// /home/vonnewmann/Documentos/Proyecto/data/leerLU.txt
	// /home/vonnewmann/Documentos/Proyecto/data/leer2

	//p.rref();
	for(int i=0;i<h.getM();i++){
		for(int j=0;j<h.getN();j++){
			cout << h.getNum(i,j)<<" ";
		}
		cout<<endl;
	}

	/*for(int i=0;i<p.getM();i++){
			for(int j=0;j<p.getN();j++){
				cout << p.getNum(i,j)<<"     ";
			}
			cout<<endl;*/
		}
	//cout<<"---------------------------------------"<<endl;
	//vector<double> y=p.SolvGaussJordan();
	// vector<double> t=p.solwithLU();   // Para leerLU


	/*for(int i=0;i<y.size();i++){
		std::cout<< y[i]<<"  ";  //leer 2
	}
	std::cout<<std::endl;*/



	return 0;
}
