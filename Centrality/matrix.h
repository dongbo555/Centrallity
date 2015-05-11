#ifndef Matrix_H
#define Matrix_H
//Definition of Myself class and related functions here
#include<vector>
using namespace std;
class Matrix{
	
public:
	//���캯��
	Matrix();

	Matrix(Matrix &matrix);

	Matrix(int row);

	Matrix(int row, vector< vector<double> > data);

	//����Խ���
	Matrix(int row, vector<double> data);

	//����ת��
	Matrix Transform();
	//�������
	Matrix Inverse();
	//���������ֵ
	double MaxEigenvalues();
	//����������
	vector<double> Eigenvector(double value);
	//����˷�
	Matrix Multiply(Matrix matrix);

	//��������ֵ���
	Matrix MulValue(double num);

	//�������������
	vector<double> MulVector(vector<double> temp);

	//����ӷ�
	Matrix Add(Matrix matrix);

	//��ȡ�����е�����
	vector<vector<double>> getMatrixData();

	//��ȡ�����еĽڵ���
	int getMatrixNode();
	//��ӡ����
	void Print();

private:

	int row;
	//��̬��ά����
	vector< vector<double> > data;

};
#endif