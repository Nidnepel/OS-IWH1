using namespace std;
vector<vector<int> >lst;
vector<bool >used;
vector<int>ans;
vector<int>d;
vector<int>p;

void bfs(int s){
	queue<int>q;
	q.push(s);
	used[s] = true;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (size_t i = 0; i < lst[v].size(); ++i) {
			int to = lst[v][i];
			if (!used[to]) {
				used[to] = true;
				q.push(to);
				d[to] = d[v] + 1;
				p[to] = v;
			}
		}
	}
}
int main() {
	int n;
	int v, to;
	cin >> n;
	
	int a;
	lst.resize(n);
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			cin >> a;
			if (a == 1)lst[i].push_back(j);
		}
	}
	vector<vector<int> >lst(n);
	cin >> v >> to;
	v--;
	to--;
	used.resize(n);
	d.resize(n);
	d[0] = 0;
	p.resize(n);
	p[v] = -1;
	used[v] = 1;
	bfs(v);
	if (!used[to]){
		cout << -1;
		return 0;
	}
	if (d[to]!=0){
		vector<int> path;
		for (int v = to; v != -1; v = p[v])
			path.push_back(v);
		reverse(path.begin(), path.end());
		cout << d[to] << endl;
		for (size_t i = 0; i<path.size(); ++i)
			cout << path[i] + 1 << " ";
	}
	else cout << 0;
	return 0;
}