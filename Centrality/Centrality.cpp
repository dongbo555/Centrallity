// homework_2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "matrix.h"
#include "centrality.h"
#include<iostream>
#include<stack> 
int _tmain(int argc, _TCHAR* argv[])
{
	int number;	
	bool judge = true;
	int row = 0; //矩阵的行和列数
	cout << "please input the number of node:" << endl;
	cin >> row;
	Matrix mat = Matrix(row);
	while (judge){
		cout << "please choose a centrality method?" << endl;
		cout << "==========================================" << endl;
		cout << "1.degree centrality" << endl;
		cout << "2.eigenvector centrality" << endl;
		cout << "3.Katz centrality" << endl;
		cout << "4.PageRank centrality" << endl;
		cout << "5.betweenness centrality" << endl;
		cout << "6.closeness centrality" << endl;
		cout << "==========================================" << endl;
		cout << "please enter the method number:" << endl;
		cin >> number;
		switch (number)
		{
		case 1:
			cout << "==========================================" << endl;
			cout << "degree centrality" << endl;
			degree(mat);
			break;
		case 2:
			cout << "==========================================" << endl;
			cout << "eigenvector centrality" << endl;
			eigenvector(mat);
			break;
		case 3:
			cout << "==========================================" << endl;
			cout << "Katz centrality" << endl;
			Katz(mat);
			break;
		case 4:
			cout << "==========================================" << endl;
			cout << "PageRank centrality" << endl;
			PageRank(mat);
			break;
		case 5:
			cout << "==========================================" << endl;
			cout << "betweenness centrality" << endl;
			betweenness(mat);
			break;
		case 6:
			cout << "==========================================" << endl;
			cout << "closeness centrality" << endl;
			closeness(mat);
			break;
		case 7:
			judge = false;
			exit(0);
		default:
			cout << "Your input error! please enter again:" << endl;
			cin >> number;
			break;
		}
		cout << "Are you exit this program ?(Y/N)" << endl;
		char t;
		cin >> t;
		if (t == 'Y' || t == 'y')
			judge = false;

	}
	return 0;
}

