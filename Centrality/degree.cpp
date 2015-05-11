#include "stdafx.h"
#include "matrix.h"
#include<iostream>

void degree(Matrix mat){
	vector< vector<double> > matrix = mat.getMatrixData();
	vector<int> count;  //存放每个节点的邻居个数
	int row = mat.getMatrixNode();
	count.resize(row);
	for (int i = 0; i < row; i++){
		count[i] = 0;
		for (int j = 0; j < row; j++){
			if (i == j) continue;
			if (matrix[j][i] == 1){
				count[i]++;
			}
		}
	}
	cout << "The node degree centrality as follow:" << endl;
	cout << "==========================================" << endl;
	for (int i = 0; i < row; i++){
		cout << "v" << i + 1 << ":" << count[i] << endl;
	}
	cout << "==========================================" << endl;
}