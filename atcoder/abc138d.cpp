#include <bits/stdc++.h>

using namespace std;

using ll=long long ;
void solve() {
    int n, q;
    cin >> n >> q;
    vector<vector<int>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    vector<ll> hint(n, 0);
    while (q--) {
        int i, x;
        cin >> i >> x;
        i--;
        hint[i] += x;
    }
    vector<ll> res(n, 0);
    function<void(int, int)> dfs = [&](int u, int p){
        for (int v: g[u]) {
            if (v == p) continue;
            res[v] += res[u] + hint[v];
            dfs(v, u);
        }
    };
    res[0] = hint[0];
    dfs(0, -1);
    for (auto& x: res) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
