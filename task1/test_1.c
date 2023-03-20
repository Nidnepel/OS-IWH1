const int inf = 1e9 + 500, MOD = 1e9 + 100;

void solve() {
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> g(n);
    vector<int> w(n);
    cin >> w;
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int st, to;
        cin>>st>>to;
        --to;
        --st;
        g[st].push_back({to, w[st]});
        g[to].push_back({st, w[to]});
    }
    priority_queue<pair<int, int>> q;
    vector<int> d(n, inf);
    q.push({0, 0});
    d[0] = 0;
    while (!q.empty()) {
        int v = q.top().second, dist = -q.top().first;
        q.pop();
        if (dist > d[v])continue;
        for (auto &el: g[v]) {
            int to = el.first, we = el.second;
            if (d[to] > d[v] + we) {
                d[to] = d[v] + we;
                q.push({-d[to], to});
            }
        }
    }
    cout << (d[n - 1] == inf? -1: d[n - 1]);
}

signed main() {
#ifdef NIDNEPEL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    quickIN;
    cout << fixed << setprecision(20);
    int t = 1;
    //   cin >> t;
    while (t--) {
        solve();
    }
}