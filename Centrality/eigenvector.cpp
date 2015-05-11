#include "stdafx.h"
#include "matrix.h"
#include<iostream>
void eigenvector(Matrix mat){	
	int row = mat.getMatrixNode();
	double temp = mat.MaxEigenvalues();
	vector<double> values = mat.Eigenvector(temp);
	cout << "The node eigenvector centrality as follow:" << endl;
	cout << "==========================================" << endl;
	for (int i = 0; i < row; i++){
		cout << "v" << i + 1 << ":" << values[i] << endl;
	}
	cout << "==========================================" << endl;
}