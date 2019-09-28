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
        g[x].emplace_back(y);
    }

    int root;

    const int INF = 0x3f3f3f3f;
    int mi_len = INF;
    vector<int> trk(n, 0);
    vector<int> pth;
    vector<int> res;
    function<void(int)> dfs = [&](int u){
        trk[u] = 1;
        pth.emplace_back(u);
        for (int v: g[u]){
            if (v == root && (int)pth.size() < mi_len) {
                mi_len = pth.size();
                res.clear();
                res = pth;
            }
            if (!trk[v]) dfs(v);
        }
        pth.pop_back();
    };
    for (int i = 0; i < n; i++) {
        // fresh as root, no need O(n) dfs, since n*m enough, and this method easy
        fill(trk.begin(), trk.end(), 0);
        root = i; dfs(i);
    }
    if (mi_len < INF) {
        cout << mi_len << "\n";
        for (auto& x: res) {
            cout << (x+1) << "\n";
        }
    } else cout << -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
