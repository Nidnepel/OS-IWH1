#include<iostream>
#include <vector>
#include<queue>
#include <algorithm>
using namespace std;
int main() {
	int n, i, j, k, x1, y1, x2, y2, u, v;
	queue< pair<int, int> >q;
	int x[8] = { -2, -2, -1, -1, 1, 1, 2, 2 },
		y[8] = { -1, 1, -2, 2, -2, 2, -1, 1 };
	cin >> n;
	vector< vector<int> >d(n + 1, vector<int>(n + 1));
	vector< vector<pair<int, int> > >p(n+1,vector<pair<int,int> >(n+1));
	for (i = 0; i <= n; ++i)
	for (j = 0; j <= n; ++j)
		d[i][j] = 1000000000;
	cin >> x1 >> y1 >> x2 >> y2;
	p[x1][y1].first = x1;
	p[x1][y1].second = y1;
	d[x1][y1] = 0;
	q.push(make_pair(x1, y1));
	while (!q.empty()) {
		i = q.front().first;
		j = q.front().second;
		q.pop();
		for (k = 0; k < 8; ++k) {
			u = i + x[k];
			v = j + y[k];
			if (u > 0 && u <= n && v > 0 && v <= n && d[u][v] > d[i][j] + 1) {
				p[u][v].first = i;
				p[u][v].second = j;
				d[u][v] = d[i][j] + 1;
				q.push(make_pair(u, v));
			}
		}
	}
 	if (d[x2][y2] == 1000000000){
		cout << -1;
	}
	else if (d[x2][y2] == 0)cout << 0;
	else{
		cout << d[x2][y2] << endl;
		vector<pair<int,int> > path;
		int l=0, m=0;
		for (pair<int, int>ve = { x2, y2 }; ve.first != x1 || ve.second!=y1; ve = p[ve.first][ve.second])
			path.push_back(ve);
		reverse(path.begin(), path.end());
		cout << x1 << " " << y1<<endl;
		for (size_t t = 0; t < path.size(); ++t){
			x1 = path[t].first;
			y1 = path[t].second;
			cout << x1 << " " << y1 << endl;
		}
	}
	system("pause");
	return 0;
}