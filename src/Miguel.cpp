#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void MultFila(vector<double> &vec, double escalar);
vector<double> operator+(vector<double> vec, vector<double> vec2);
void GaussJordan(vector <vector <double> > &matrix);


int main(){
	vector <vector<double> > matrix = {{9,32,13,8}, {24,35,33,5},{22,37,32,24}};
	vector<double> b = {1,2,3};
	for(int i=0;i<matrix.size();i++){
		for(int j=0;j<matrix[0].size();j++){
			cout << matrix[i][j]<<" ";
		}
		cout <<endl;
	}
	cout << "-------------------"<<endl;
	GaussJordan(matrix);

	for(int i=0;i<matrix.size();i++){
		for(int j=0;j<matrix[0].size();j++){
			cout << matrix[i][j]<<" ";
		}
		cout <<endl;
	}
	cout << "-------------------"<<endl;








	return 0;
}

void MultFila(vector<double> &vec, double escalar){
	for(int i=0;i<vec.size();i++){
		vec[i] *= escalar;
	}
}

vector<double> operator+(vector<double> vec, vector<double> vec2){
	vector<double> suma(vec.size());
	for(int i=0;i<vec.size();i++){
		suma[i]=vec2[i]+vec[i];
	}
	return suma;
}

void GaussJordan(vector <vector <double> > &matrix){
	int j=0, i;
	for(int p=0;p<matrix.size();p++){
		bool success =false;
		i=p;
		while((j<matrix[0].size()) && !success){
			i=p;
			while(i<matrix.size()){
				if(matrix[i][j] != 0){
					success = true;
					break;
				}
				i++;
			}
			j++;
		}
		if(success){
			if(i != p) matrix[p].swap(matrix[i]);
			MultFila(matrix[p], (1.0/matrix[p][j-1]));
			for(int k=p+1;k<matrix.size();k++){
				vector <double> temp = matrix[p];
				MultFila(temp, -matrix[k][j-1]);
				matrix[k] = matrix[k]+ temp;
				for (int l=0;l<matrix[0].size();l++){
					if (abs(matrix[k][l])<= 1e-11)
						matrix[k][l] = 0;
				}

			}

		}


	}


	for(int i=matrix.size()-1;i != 0; i--){
		for(int j=0;j<matrix[0].size();j++){
			if(abs(matrix[i][j]-1)< 1e-10){
				matrix[i][j]=1;
				for(int k=i-1; k!=-1;k--){
					vector <double>temp= matrix[i];
					MultFila(temp,-matrix[k][j]);
					matrix[k] = matrix[k]+temp;
				}
			}
		}
	}





}
