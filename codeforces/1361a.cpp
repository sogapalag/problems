#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        --x;--y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    // if exist valid, id must be
    sort(id.begin(), id.end(), [&](auto& u, auto& v){
        return a[u] < a[v];
    });
    vector<int> mex(n, 1);
    for (int i:id) {
        if (mex[i] != a[i]) {
            cout << -1; return;
        }
        for (int j:g[i]) if (mex[j]==a[i]) ++mex[j];
    }
    for (int i:id) cout << i+1 << ' ';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
