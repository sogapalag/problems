#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// best form a->i->b->i->c
void solve() {
    int n,m,a,b,c;
    cin >> n >> m >> a >> b >> c;
    --a,--b,--c;
    vector<int> p(m);
    for (auto& x: p) cin >> x;
    sort(p.begin(), p.end());
    vector<ll> sum(m+1);
    for (int i = 0; i < m; i++) {
        sum[i+1] = sum[i] + p[i];
    }
    vector<vector<int>> g(n);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    auto getdis = [&](int s){
        vector<int> d(n, -1);
        queue<int> q;
        d[s]=0; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v:g[u]) if(d[v]==-1){
                d[v] = d[u]+1;
                q.push(v);
            }
        }
        return d;
    };
    auto da = getdis(a);
    auto db = getdis(b);
    auto dc = getdis(c);

    ll res = 1ll<<61;
    for (int i = 0; i < n; i++) {
        int x = da[i];
        int y = db[i];
        int z = dc[i];
        if (x+y+z <= m) {
            res = min(res, sum[x+y+z] + sum[y]);
        }
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
