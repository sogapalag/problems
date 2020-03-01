#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[y].push_back(x); // rev
    }
    int k; cin >> k;
    vector<int> a(k);
    for (auto& x: a) {
        cin >> x; x--;
    }
    int t = a.back();
    vector<int> d(n, -1);
    vector<bool> dup(n);
    {
        d[t] = 0;
        queue<int> q; q.push(t);
        while (!q.empty()) {
            auto u = q.front(); q.pop();
            for (int v:g[u]) {
                if (d[v] == -1) {
                    d[v] = d[u] + 1;
                    // the problem said, if next(v) at shortest u->t, won't rebuild. so below comment
                    //dup[v] = dup[v] || dup[u];
                    q.push(v);
                } else if (d[v] == d[u]+1){
                    dup[v] = true;
                }
            }
        }
    }
    int mi = 0;
    for (int i = k-2; i >= 0; i--) {
        int u = a[i], v = a[i+1];
        if (d[u] != d[v]+1) mi++;
    }
    cout << mi << ' ';

    int mx = 0;
    for (int i = k-2; i >= 0; i--) {
        int u = a[i], v = a[i+1];
        if (d[u] < d[v]+1) {
            mx++;
        } else if (dup[u]) {
            mx++;
        }
    }
    cout << mx;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
