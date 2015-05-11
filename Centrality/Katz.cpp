#include "stdafx.h"
#include "matrix.h"
#include<iostream>

void Katz(Matrix mat){
	int row = mat.getMatrixNode();
	double temp = mat.MaxEigenvalues();
	double a, b;
	cout << "please input ¦Á(¦Á<" << 1 / temp << ")and ¦Â:" << endl;
	cin >> a >> b;
	//vector<double> values = mat.Eigenvector(temp);
	vector<vector<double>> matrixData = mat.Transform().MulValue(a).getMatrixData();
	//Çó£¨I-aAT£©
	for (int i = 0; i < row; i++){
		for (int j = 0; j < row; j++){
			if (i == j){
				matrixData[i][j] = 1 - matrixData[i][j];
			}
			else{
				matrixData[i][j] = -matrixData[i][j];
			}
		}
	}
	Matrix mat1 = Matrix(row, matrixData);
	vector<double> t1(row);
	for (int i = 0; i < row; i++){
		t1[i] = 1;
	}
	vector<double> values = mat1.Inverse().MulValue(b).MulVector(t1);
	cout << "The node Katz centrality as follow:" << endl;
	cout << "==========================================" << endl;
	for (int i = 0; i < row; i++){
		cout << "v" << i + 1 << ":" << values[i] << endl;
	}
	cout << "==========================================" << endl;
}