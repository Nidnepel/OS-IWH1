
int pow2(int x) {
	return (1ll << x);
}

const int inf = 1e9, MOD = 1e9 + 7;

void out(vector<vector<int>>& m) {
	loop(m) cout << el << nl;
}

//4
//4
//0 0 0 1
//0 0 0 2
//0 0 0 0
//0 0 0 0

void solve() {
	int n, m;
	cin >> n >> m;
	vector< vector<int> >matrix(n, vector<int>(m));
	vector<vector<int>>used(n, vector<int>(m, 0));
	queue< pair<int, int> >q;
	q.push({ 0, 0 });
	vector< vector<int> >d(n, vector<int>(m, inf));
	int i, j;
	for (int l = 0; l < n; l++) {
		for (int t = 0; t < m; t++) {
			cin >> matrix[l][t];
		}
	}
	int k, u, v;
	int x[4] = { -1, 1, 0, 0 },
		y[4] = { 0, 0, 1, -1 };
	d[0][0] = 0;
	while (!q.empty()) {
		i = q.front().first;
		j = q.front().second;
		used[i][j] = 1;
		q.pop();
		for (k = 0; k < 4; ++k) {
			u = i;
			v = j;
			while (u + y[k] < n && v + x[k] < m && u + y[k] >= 0 && v + x[k] >= 0 && (matrix[u + y[k]][v + x[k]] == 0 || matrix[u + y[k]][v + x[k]] == 2)) {
				u += y[k];
				v += x[k];
				if (matrix[u][v] == 2) {
					d[u][v] = d[i][j] + 1;
//					out(d);
					cout << d[u][v];
					return;
				}
			}
			if (!used[u][v]) {
				//cout << u << " " << v << nl;
				q.push({ u, v });
				if(d[u][v] > d[i][j] + 1)d[u][v] = d[i][j] + 1;
			}
		}
	}
}


signed main() {
	quickIN;
	int t = 1;
	//cin >> t;
	while (t--) {
		solve();
	}
}