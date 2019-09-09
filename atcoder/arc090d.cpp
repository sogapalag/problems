#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> g(n);
    for (int _ = 0; _ < m; _++) {
        int x,y,c;
        cin >> x >> y >> c;
        x--; y--;
        g[x].emplace_back(y,c);
        g[y].emplace_back(x,-c);
    }
    vector<long long> d(n);
    function<void(int)> dfs = [&](int u){
        for (auto& p: g[u]) {
            int v,c;
            tie(v,c) = p;
            if (d[v]) {
                if (d[u]+c != d[v]) {
                    cout << "No"; exit(0);
                }
            } else {
                d[v] = d[u]+c;
                dfs(v);
            }
        }
    };
    for (int i = 0; i < n; i++) {
        if (!d[i]) {
            d[i] = 1ll<<40;
            dfs(i);
        }
    }
    cout << "Yes";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
