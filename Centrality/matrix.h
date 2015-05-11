#ifndef Matrix_H
#define Matrix_H
//Definition of Myself class and related functions here
#include<vector>
using namespace std;
class Matrix{
	
public:
	//构造函数
	Matrix();

	Matrix(Matrix &matrix);

	Matrix(int row);

	Matrix(int row, vector< vector<double> > data);

	//构造对角阵
	Matrix(int row, vector<double> data);

	//矩阵转置
	Matrix Transform();
	//求逆矩阵
	Matrix Inverse();
	//求最大特征值
	double MaxEigenvalues();
	//求特征向量
	vector<double> Eigenvector(double value);
	//矩阵乘法
	Matrix Multiply(Matrix matrix);

	//矩阵与数值相乘
	Matrix MulValue(double num);

	//矩阵与向量相乘
	vector<double> MulVector(vector<double> temp);

	//矩阵加法
	Matrix Add(Matrix matrix);

	//获取矩阵中的数据
	vector<vector<double>> getMatrixData();

	//获取矩阵中的节点数
	int getMatrixNode();
	//打印矩阵
	void Print();

private:

	int row;
	//动态二维数组
	vector< vector<double> > data;

};
#endif