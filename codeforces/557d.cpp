#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n,m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    vector<int> deg(n);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        deg[x]++;deg[y]++;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vector<bool> trk(n);
    vector<int> depth(n);
    bool has_odd = false;
    ll sum = 0;
    ll l,r;
    function<void(int)> dfs = [&](int u){
        trk[u] = true;
        if (depth[u]&1) l++;
        else r++;
        for (int v:g[u]) {
            if (trk[v]) {
                if ((depth[u]-depth[v])%2 == 0) has_odd = true;
            } else {
                depth[v] = 1 + depth[u];
                dfs(v);
            }
        }
    };
    for (int i = 0; i < n; i++) {
        if (!trk[i]) {
            l = 0, r = 0;
            dfs(i);
            sum += l*(l-1)/2;
            sum += r*(r-1)/2;
        }
    }

    if (has_odd) {
        cout << "0 1"; return;
    }
    
    //  \/, dup, e.g. square, lack, e.g. ----
    // should consider bip.
    //ll sum = 0;
    //for (ll x: deg)if(x>=2){
    //    sum += x * (x-1) / 2;
    //}
    if (sum > 0) {
        cout << "1 " << sum; return;
    }

    // (/, .)
    if (m > 0) {
        cout << "2 " << (m*1ll*(n-2)); return;
    }

    cout << "3 " << (1ll*n*(n-1)*(n-2)/6);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
