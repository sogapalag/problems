#include <bits/stdc++.h>

using namespace std;


// considered dist.. rather min. but should similar greedy method
void solve() {
    int n; cin >> n;
    vector<vector<pair<int,int>>> g(n);
    for (int i = 1; i < n; i++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].emplace_back(y,i);
        g[y].emplace_back(x,i);
    }
    vector<int> f(n, 1e6);
    vector<int> pth;
    int T;
    // next time try impl lca-style, while(u!=v). might be impl-faster
    function<bool(int,int)> dfs = [&](int u, int p){
        for (auto& e: g[u]) {
            int v,i;
            tie(v,i) = e;
            if (v==p) continue;
            pth.push_back(i);
            if (v == T) return true;
            if (!dfs(v, u)) pth.pop_back();
            else return true;
        }
        return false;
    };
    int m; cin >> m;
    vector<pair<int, int>> qs(m);
    vector<int> dis(m);
    vector<vector<int>> path(m);
    for (int i = 0; i < m; i++) {
        int x,y,z;
        cin >> x >> y >> z;
        x--;y--;
        qs[i] = {x,y};
        dis[i] = z;
    }
    vector<int> id(m);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](auto& u, auto& v){
        return dis[u] < dis[v];
    });
    auto ensure = [](bool x){
        if (!x) {
            cout << -1; exit(0);
        }
    };
    for (int _:id) {
        int x,y;
        tie(x,y) = qs[_];
        int z = dis[_];
        pth.clear(); T = y; dfs(x, -1);
        path[_] = pth;
        for (int i: pth) {
            f[i] = z;
        }
    }
    for (int _ = 0; _ < m; _++) {
        int mi = 1e6;
        int z = dis[_];
        for (int i: path[_]) mi = min(mi, f[i]);
        ensure(mi == z);
    }

    for (int i = 1; i < n; i++) {
        cout << f[i] << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
