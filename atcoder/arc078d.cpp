#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    vector<int> pa(n,-1);
    vector<int> sz(n, 1);
    function<void(int,int)> dfs = [&](int u, int p){
        for (int v: g[u])if(v!=p){
            pa[v] = u;
            dfs(v,u);
            sz[u] += sz[v];
        }
    };
    dfs(0, -1);
    int d = 0, x = n-1;
    while (x != 0) {
        x = pa[x];
        d++;
    }
    d = (d-1)/2;
    x = n-1;
    while (d--) {
        x = pa[x];
    }

    int b = sz[x], a = n - b;
    cout << (a>b?"Fennec":"Snuke");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
