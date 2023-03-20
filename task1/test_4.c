#include<iostream>
#include <vector>
#include<queue>
#include <algorithm>
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	vector< vector<int> >matrix(n, vector<int>(m));
	queue< pair<int, int> >q;	
	vector< vector<int> >d(n, vector<int>(m));
	int  i, j;
	for (i = 0; i < n; ++i)
	for (j = 0; j < m; ++j)
	d[i][j] = 1000000000;	

	for (int l = 0; l < n; l++){
		for (int t = 0; t < m; t++){
			cin >> matrix[l][t];
			if (matrix[l][t] == 1){
				d[l][t] = 0;
				q.push(make_pair(l, t));
			}
		}
	}
	int k, u, v;
	int x[4] = { -1, 1, 0, 0 },
		y[4] = { 0, 0, 1, -1 };
	while (!q.empty()) {
		i = q.front().first;
		j = q.front().second;
		q.pop();
		for (k = 0; k < 4; ++k) {
			u = i + x[k];
			v = j + y[k];
			if (u >= 0 && u < n && v >= 0 && v < m &&d[u][v]>d[i][j]+1 ) {
				d[u][v] = d[i][j] + 1;
				q.push(make_pair(u, v));
			}
		}
	}
	for (i = 0; i < n; ++i){
		for (j = 0; j < m; ++j)
			cout << d[i][j]<<" ";
		cout << endl;
	}
	system("pause");
	return 0;
}