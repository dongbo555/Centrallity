#include "stdafx.h"
#include "matrix.h"
#include<iostream>
#define MAX LONG_MAX
void closeness(Matrix m){
	int row = m.getMatrixNode();
	vector<vector<double>> matrixData = m.getMatrixData();
	vector<double> values(row);
	for (int i = 0; i < row; i++){
		for (int j = 0; j < row; j++){
			if (matrixData[i][j] <= 0){
				matrixData[i][j] = MAX;
			}
		}
	}
	for (int i = 0; i < row; i++){
		for (int j = 0; j < row; j++){
			for (int k = 0; k < row; k++){
				if (matrixData[i][j] + matrixData[k][i] < matrixData[k][j]){
					matrixData[k][j] = matrixData[i][j] + matrixData[k][i];
				}
			}
		}
	}
	for (int i = 0; i < row; i++){
		double temp = 0;
		for (int j = 0; j < row; j++){
			if (i == j)continue;
			temp += matrixData[j][i];
		}
		values[i] = 1 / (temp / (row - 1));
	}
	cout << "The node closeness centrality as follow:" << endl;
	cout << "==========================================" << endl;
	for (int i = 0; i < row; i++){
		cout << "v" << i + 1 << ":" << values[i] << endl;
	}
	cout << "==========================================" << endl;
}

