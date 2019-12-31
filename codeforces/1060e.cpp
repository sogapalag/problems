#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// note each path -> ceil(len/2)
// a method is consider lca=u, maintain |X| and sum_X dis. by pairty. aka half arm trick.
// below is use fomula that. res*2 = all_dis + #odd_dis. i.e. fill ceil needed
void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    ll res = 0;
    vector<int> sz(n,1), dif(n,0);//subsz parity differ
    vector<int> dep(n);
    function<void(int,int)> dfs = [&](int u,int p){
        for(int v:g[u])if(v!=p){
            dep[v] = dep[u] + 1;//unused
            dfs(v,u);
            res += sz[v] * 1ll * (n-sz[v]); // contribution on edge trick
            res += (sz[u]-dif[u]) * 1ll * (sz[v] - dif[v]);
            res += dif[u] * 1ll * dif[v];
            sz[u] += sz[v];
            dif[u] += sz[v] - dif[v];
        }
    };
    dfs(0,-1);
    res /= 2;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
