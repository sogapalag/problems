#include <bits/stdc++.h>

using namespace std;
using ll=long long;
// for edge contribution, G is at least, since odd. sufficient by the rule assign.
// B is upper bound for sure. valid assignment, let C be centroid. in dfs order assign [1..k][1..k]
void solve() {
    int n; cin >> n;
    n *= 2;
    vector<vector<pair<int,int>>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x,y,z;
        cin >> x >> y >> z;
        x--;y--;
        g[x].emplace_back(y,z);
        g[y].emplace_back(x,z);
    }
    ll G = 0, B = 0;
    vector<int> sz(n, 1);
    function<void(int,int)> dfs = [&](int u,int p){
        for (auto& _: g[u]) {
            int v,z;
            tie(v,z) = _;
            if(v==p)continue;
            dfs(v, u);
            if (sz[v]&1) G += z;
            B += z * 1ll* min(sz[v], n-sz[v]);
            sz[u]+=sz[v];
        }
    };
    dfs(0,-1);
    cout << G<<' '<<B<<'\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
