#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    vector<int> co(m);
    for (int i = 0; i < m; i++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].emplace_back(y);
        co[i] = x>y ? 1: 2;
    }
    int sta=1, fin=2;
    vector<int> trk(n);
    function<bool(int)> dfs = [&](int u){
        trk[u] = sta;
        for (int v: g[u]) {
            if (trk[v] < sta) {
                if (dfs(v)) return true;
            } else if (trk[v] < fin) {
                return true;
            }
        }
        trk[u] = fin;
        return false;
    };
    bool has_cycle = false;
    for (int i = 0; i < n; i++) {
        if (!trk[i]) has_cycle |= dfs(i);
    }
    int res = 2;
    if (!has_cycle) res=1, fill(co.begin(), co.end(), 1);
    cout << res << "\n";
    for (auto& x: co) {
        cout << x << ' ';
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
