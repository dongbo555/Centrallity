#include "stdafx.h"
#include"matrix.h"
#include<iostream>
#include <math.h>
using namespace std;
#define MIN_VALUE 1e-14  //������Ҫ�������ֵ
#define IS_DOUBLE_ZERO(d) ((abs(d)) < MIN_VALUE ? 0:(d))
#define SIGN(d) ((d) < 0 ? (-1): 1)          //((d==0)?0:1))
//�������
Matrix::Matrix(int row){
	cout << "please input the matrix data by row:" << endl;
	Matrix::row = row;
	Matrix::data.resize(row);
	for (int i = 0; i < row; i++){
		Matrix::data[i].resize(row);
	}
	for (int i = 0; i < row; i++){
		for (int j = 0; j < row; j++){
			cin >> Matrix::data[j][i];
		}
	}
}
Matrix::Matrix(int row, vector< vector<double> > data){
	Matrix::row = row;
	Matrix::data.resize(row);
	for (int i = 0; i < row; i++){
		Matrix::data[i].resize(row);
		for (int j = 0; j < row; j++){
			Matrix::data[i][j] = data[i][j];
		}
	}
}
Matrix::Matrix(Matrix &matrix){
	Matrix::row = matrix.row;
	for (int i = 0; i < matrix.row; i++){
		Matrix::data.push_back(matrix.data[i]);
	}
}

//����Խ���
Matrix::Matrix(int row, vector<double> data){
	Matrix::row = row;
	Matrix::data.resize(row);
	for (int i = 0; i < row; i++){
		Matrix::data[i].resize(row);
		for (int j = 0; j < row; j++){
			if (i == j){
				Matrix::data[i][j] = data[i];
			}
			else{
				Matrix::data[i][j] = 0;
			}
		}
	}
}

//����ת��
Matrix Matrix::Transform(){
	Matrix temp = Matrix(Matrix::row, Matrix::data);
	for (int i = 0; i < row; i++){
		for (int j = 0; j < i; j++){
			double t = temp.data[i][j];
			temp.data[i][j] = temp.data[j][i];
			temp.data[j][i] = t;
		}
	}
	return temp;
}
//ʵ������
Matrix Matrix::Inverse(){
	Matrix temp = Matrix(Matrix::row, Matrix::data);
	vector< vector<double> > matr(row);
	for (int i = 0; i < row; i++){
		matr[i].resize(row);
		for (int j = 0; j < row; j++){
			if (j == i){
				matr[i][j] = 1;
			}
			else{
				matr[i][j] = 0;
			}
		}
	}
	//��˹����
	for (int i = 0; i < row; i++){
		//����ֵ��������Ϊ��Ԫ��
		double max = abs(temp.data[i][i]);
		int k = i;
		for (int j = i; j < row; j++){
			if (abs(temp.data[i][j]) > max){
				max = abs(temp.data[i][j]);
				k = j;
			}
		}
		//�жϾ����Ƿ����
		if (max == 0){
			cout << "����ǿ������" << endl;
			return temp;
		}
		if (k != i){
			for (int m = 0; m < row; m++){
				double t = temp.data[m][i];
				temp.data[m][i] = temp.data[m][k];
				temp.data[m][k] = t;
				t = matr[m][i];
				matr[m][i] = matr[m][k];
				matr[m][k] = t;
			}
		}
		//��˹��������
		double x = temp.data[i][i];
		for (int n = 0; n < row; n++){
			if (n >= i){
				temp.data[n][i] = temp.data[n][i] / x;
			}
			matr[n][i] = matr[n][i] / x;
		}
		for (int m = 0; m < row; m++){
			if (m == i){
				continue;
			}
			else{
				x = temp.data[i][m];
				for (int n = 0; n < row; n++){
					if (n >= i){
						temp.data[n][m] = temp.data[n][m] - x*temp.data[n][i];
					}
					matr[n][m] = matr[n][m] - x * matr[n][i];
				}
			}
		}
	}
	for (int i = 0; i < row; i++){
		for (int j = 0; j < row; j++){
			temp.data[j][i] = IS_DOUBLE_ZERO(matr[j][i]);
		}
	}
	return temp;
}
//�������
Matrix Matrix::Multiply(Matrix matrix){
	Matrix temp = Matrix(Matrix::row, Matrix::data);
	for (int i = 0; i < row; i++){
		for (int j = 0; j < row; j++){
			temp.data[i][j] = 0;
			for (int k = 0; k < row; k++){
				temp.data[i][j] += Matrix::data[k][j] * matrix.data[i][k];
			}
			temp.data[i][j] = IS_DOUBLE_ZERO(temp.data[i][j]);
		}
	}
	return temp;
}

//��������ֵ���
Matrix Matrix::MulValue(double num){
	Matrix temp = Matrix(Matrix::row, Matrix::data);
	for (int i = 0; i < row; i++){
		for (int j = 0; j < row; j++){
			temp.data[j][i] = temp.data[j][i]*num;
		}
	}
	return temp;
}

//�������
Matrix Matrix::Add(Matrix matrix){
	Matrix temp = Matrix(Matrix::row, Matrix::data);
	for (int i = 0; i < row; i++){
		for (int j = 0; j < row; j++){
			temp.data[i][j] = temp.data[i][j] + matrix.data[i][j];
		}
	}
	return temp;
}
//������ֵ  ����householder����QR�ֽ�
double Matrix::MaxEigenvalues(){
	double values = 0;
	Matrix r = Matrix(Matrix::row, Matrix::data);
	vector< double > c(row), e(row), v(row);
	bool sym = true;
	//�жϾ����Ƿ���ʵ�Գƾ���
	for (int i = 0; i < row; i++){
		for (int j = 0; j < row; j++){
			if (r.data[i][j] != r.data[j][i])
				sym = false;
		}
	}
	int count;
	//if (sym == false){ //������ǵĻ�����
	for (count = 0; count < 1000; count++){
		vector< vector<double> > q(row), temp(row);
		for (int i = 0; i < row; i++){
			q[i].resize(row);
			temp[i].resize(row);
		}
		//��������������ֵ
		for (int i = 0; i < row - 1; i++){
			//���c,e
			for (int j = 0; j < row; j++){
				if (j < i){
					c[j] = 0;
					e[j] = 0;
				}
				else{
					c[j] = r.data[i][j];
					e[j] = 0;
					if (j == i){
						if (c[i] > 0){
							e[i] = 1;
						}
						else{
							e[i] = -1;
						}
					}
				}
			}
			//��v
			double c2 = 0;
			for (int j = 0; j < row; j++){ //��C�����ķ���
				c2 += c[j] * c[j];
			}
			c2 = sqrt(c2);
			for (int j = 0; j < row; j++){
				v[j] = c[j] + c2*e[j];
			}

			//����������H
			double v2 = 0;
			for (int j = 0; j < row; j++){ //��VTV
				v2 += v[j] * v[j];
			}
			vector< vector<double> > vt(row);
			for (int j = 0; j < row; j++){
				vt[j].resize(row);
				for (int k = 0; k < row; k++){
					vt[j][k] = v[j] * v[k];
				}
			}
			vector< vector<double> > h(row);
			for (int j = 0; j < row; j++){
				h[j].resize(row);
				for (int k = 0; k < row; k++){
					if (k == j){
						h[j][k] = 1 - (2 * vt[j][k]) / v2;
					}
					else{
						h[j][k] = 0 - (2 * vt[j][k]) / v2;
					}
				}
			}
			//����������Q
			if (i == 0){
				for (int j = 0; j < row; j++){
					for (int k = 0; k < row; k++){
						q[j][k] = h[j][k];
					}
				}
			}
			else{
				for (int j = 0; j < row; j++){   //��t����ֵ
					temp[j].resize(row);
					for (int k = 0; k < row; k++){
						temp[j][k] = q[j][k];
					}
				}
				for (int j = 0; j < row; j++){  //t������H������˵õ���������Q
					for (int k = 0; k < row; k++){
						q[j][k] = 0;
						for (int l = 0; l < row; l++){
							q[j][k] += temp[l][k] * h[j][l];
						}
						q[j][k] = IS_DOUBLE_ZERO(q[j][k]);
					}
				}
			}
			//�������Ǿ���R
			for (int j = 0; j < row; j++){   //��temp����ֵ
				for (int k = 0; k < row; k++){
					temp[j][k] = r.data[j][k];

				}
			}
			for (int j = 0; j < row; j++){  //temp������H������˵õ������Ǿ���
				for (int k = 0; k < row; k++){
					r.data[j][k] = 0;
					for (int l = 0; l < row; l++){
						r.data[j][k] += h[l][k] * temp[j][l];
					}
					r.data[j][k] = IS_DOUBLE_ZERO(r.data[j][k]);
				}
			}

		}
		//R������Q�������
		for (int j = 0; j < row; j++){   //��temp����ֵ
			for (int k = 0; k < row; k++){
				temp[j][k] = r.data[j][k];

			}
		}
		for (int j = 0; j < row; j++){  //temp������H������˵õ������Ǿ���
			for (int k = 0; k < row; k++){
				r.data[j][k] = 0;
				for (int l = 0; l < row; l++){
					r.data[j][k] += temp[l][k] * q[j][l];
				}
				r.data[j][k] = IS_DOUBLE_ZERO(r.data[j][k]);
			}
		}
		//r.Print();
		bool check = true;
		bool check1 = true;
		//�ж�������εĵ�������Ƿ���ͬ����ͬ�Ļ�ֹͣ����
		for (int j = 0; j < row; j++){
			for (int k = 0; k < row; k++){
				if (abs(temp[j][k] - r.data[j][k]) > 1e-5){
					check1 = false;
				}
			}
		}

		//�ж��Ƿ��������Ǿ����ǵĻ�ֹͣ����
		for (int i = 0; i < row; i++){
			for (int j = row - 1; j > i; j--){
				if (r.data[i][j] != 0){
					check = false;
				}
			}
		}
		if (check == true || check1 == true){
			break;
		}
		values += 1;
		//cout<< values;
	}
	//}else{

	if (count == 1000){
		vector< vector<double> > jm(row);
		//��ʼ��J����Ϊ��λ��
		for (int i = 0; i < row; i++){
			jm[i].resize(row);
			for (int j = 0; j < row; j++){
				if (i == j){
					jm[i][j] = 1;
				}
				else{
					jm[i][j] = 0;
				}
			}
		}
		//��off��A��
		double off = 0;
		for (int i = 0; i < row; i++){
			for (int j = 0; j < row; j++){
				if (i == j){
					continue;
				}
				else{
					off += r.data[i][j] * r.data[i][j];
				}
			}
		}
		//��������
		while (abs(off) >0){
			for (int i = 0; i < row - 1; i++){
				for (int j = i + 1; j < row; j++){
					if (r.data[i][j] != 0){
						double l = (r.data[i][i] - r.data[j][j]) / (2 * r.data[i][j]);
						double t = SIGN(l) / (abs(l) + sqrt(1 + l*l));   //����tan
						double c = 1 / sqrt(1 + t*t);  //����cos
						double s = c*t;    //����sin
						double temp1 = r.data[i][i];
						double temp2 = r.data[j][j];
						r.data[i][i] = temp1*c*c + temp2*s*s + r.data[i][j] * s*c * 2;
						r.data[j][j] = temp1*s*s + temp2*c*c - r.data[i][j] * 2 * c*s;
						off -= r.data[i][j] * r.data[i][j] * 2;
						r.data[i][j] = r.data[j][i] = 0;
						//���µ�J
						vector< vector<double> > tempMatrix1(row);
						vector< vector<double> > tempMatrix2(row);
						for (int k = 0; k < row; k++){
							tempMatrix1[k].resize(row);
							tempMatrix2[k].resize(row);
							for (int m = 0; m < row; m++){
								tempMatrix1[k][m] = jm[k][m];
								if (k == m){
									if (k == i || k == j){
										tempMatrix2[k][m] = c;
									}
									else {
										tempMatrix2[k][m] = 1;
									}
								}
								else if (k == i&&m == j){
									tempMatrix2[k][m] = s;
								}
								else if (k == j&&m == i){
									tempMatrix2[k][m] = -s;
								}
								else{
									tempMatrix2[k][m] = 0;
								}
							}
						}
						//jm��Q���
						for (int k = 0; k < row; k++){  //temp������H������˵õ������Ǿ���
							for (int m = 0; m < row; m++){
								jm[k][m] = 0;
								for (int l = 0; l < row; l++){
									jm[k][m] += tempMatrix1[l][m] * tempMatrix2[k][l];
								}
								jm[k][m] = IS_DOUBLE_ZERO(jm[k][m]);
							}
						}
					}
				}
			}
		}
	}
	values = r.data[0][0];
	for (int i = 0; i < row; i++){
		if (r.data[i][i] > values){
			values = r.data[i][i];
		}
	}
	double num = (int)values;
	if (abs(values - num) < 1e-10){
		values = num;
	}
	//cout <<"�������ֵΪ��"<< values << endl;
	return values;
}
//����������
vector<double> Matrix::Eigenvector(double value){
	Matrix temp = Matrix(Matrix::row, Matrix::data);
	vector< double > vectors(row);
	for (int i = 0; i < row; i++){
		temp.data[i][i] -= value;
	}
	for (int i = 0; i < row; i++){
		//����ֵ��������Ϊ��Ԫ��
		double max = abs(temp.data[i][i]);
		int k = i;
		for (int j = i; j < row; j++){
			if (abs(temp.data[i][j]) > max){
				max = abs(temp.data[i][j]);
				k = j;
			}
		}
		if (k != i){
			for (int m = 0; m < row; m++){
				double t = temp.data[m][i];
				temp.data[m][i] = temp.data[m][k];
				temp.data[m][k] = t;
			}
		}
		//��˹��������
		double x = temp.data[i][i];
		for (int n = 0; n < row; n++){
			if (n >= i){
				temp.data[n][i] = IS_DOUBLE_ZERO(temp.data[n][i] / x);
			}
		}
		for (int m = 0; m < row; m++){
			if (m == i){
				continue;
			}
			else{
				x = temp.data[i][m];
				for (int n = 0; n < row; n++){
					if (n >= i){
						temp.data[n][m] = temp.data[n][m] - x*temp.data[n][i];
						temp.data[n][m] = (abs(temp.data[n][m]) < 1e-10 ? 0 : temp.data[n][m]);
					}
				}
			}
		}
		bool check = true;
		for (int j = 0; j < row; j++){
			if (temp.data[j][row - 1] != 0){
				check = false;
			}
		}
		if (check == true){
			break;
		}
	}
	//����������
	for (int i = 1; i <= row; i++){
		if (i == 1){
			vectors[row - i] = 1;
		}
		else{
			double t = 0;
			for (int j = 1; j < i; j++){
				t += vectors[row - j] * temp.data[row - j][row - i];
			}
			vectors[row - i] = 0 - t / temp.data[row - i][row - i];
		}
	}
	//����������Ϊ��λ����
	double t = 0;
	for (int i = 0; i < row; i++){
		t += vectors[i] * vectors[i];
	}
	t = sqrt(1 / t);
	for (int i = 0; i < row; i++){
		vectors[i] *= t;
	}
	//cout <<"����ֵ��"<<value<< "����Ӧ����������Ϊ��" << endl;
	//for (int i = 0; i < row; i++){
	//	cout << vectors[i] << "\t";
	//}
	//cout << endl;
	return vectors;
}

//�������������
vector<double> Matrix::MulVector(vector<double> temp){
	vector<double> vector(Matrix::row);
	for (int i = 0; i < row; i++){
		vector[i] = 0;
		for (int j = 0; j < row; j++){
			vector[i] += Matrix::data[j][i] * temp[j];
		}
	}
	return vector;
}

//��ȡ�����е�����
vector<vector<double>> Matrix::getMatrixData(){
	return Matrix::data;
}

int Matrix::getMatrixNode(){
	return Matrix::row;
}

//��ӡ����
void Matrix::Print(){
	for (int i = 0; i < row; i++){
		for (int j = 0; j < row; j++){
			cout << Matrix::data[j][i] << "\t";
		}
		cout << endl;
	}
}