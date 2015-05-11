#include "stdafx.h"
#include "matrix.h"
#include<iostream>

void PageRank(Matrix mat){
	int row = mat.getMatrixNode();
	double temp = mat.MaxEigenvalues();
	double a, b;
	cout << "please input ��(��<" << 1 / temp << ")and ��:" << endl;
	cin >> a >> b;
	//������Ϊ����
	vector<vector<double>> dj = mat.getMatrixData();
	vector<double> diagt(row);
	for (int i = 0; i < row; i++){
		diagt[i] = 0;
		for (int j = 0; j < row; j++){
			diagt[i] += dj[j][i];
		}
	}
	//����ԽǾ���
	Matrix diag = Matrix(row, diagt);
	vector<vector<double>> matrixData = mat.Transform().MulValue(a).Multiply(diag.Inverse()).getMatrixData();
	//��I-aAT��
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