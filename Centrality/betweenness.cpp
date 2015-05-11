#include "stdafx.h"
#include "matrix.h"
#include<iostream>
#include<stack> 
#include<queue>
#include<assert.h>
void betweenness(Matrix m){
	int row = m.getMatrixNode();
	vector<double> CB(row, 0.0);
	for (int s = 0; s < row; s++)
	{
		vector<vector<int> >P(row);
		stack<int> S;
		vector<double> sigma(row, 0.0);
		sigma[s] = 1;
		vector<int> d(row, -1);
		d[s] = 0;
		queue<int> Q;
		Q.push(s);
		while (!Q.empty())
		{
			int front = Q.front();
			Q.pop();
			S.push(front);
			for (int j = 0; j < row; j++)
			{
				if (m.getMatrixData()[front][j] == 1 && j != front)
				{
					if (d[j] < 0)
					{
						Q.push(j);
						d[j] = d[front] + 1;
					}
					if (d[j] == d[front] + 1)
					{
						sigma[j] = sigma[j] + sigma[front];
						P[j].push_back(front);

					}
				}

			}
		}
		//
		vector<double> Sigma(row, 0.0);
		while (!S.empty())
		{
			int w = S.top();
			S.pop();
			for (int i = 0; i < P[w].size(); i++)
			{
				Sigma[P[w][i]] = Sigma[P[w][i]] + (sigma[P[w][i]] / sigma[w])*(1.0 + Sigma[w]);

			}
			if (w != s)
			{
				CB[w] = CB[w] + Sigma[w];
			}
		}

	}
	//print
	
	cout << "The node betweenness centrality as follow:" << endl;
	cout << "==========================================" << endl;
	for (int i = 0; i < row; i++){
		cout << "v" << i + 1 << ":" << CB[i] << endl;
	}
	cout << "==========================================" << endl;
}