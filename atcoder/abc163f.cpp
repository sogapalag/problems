#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x; --x;
    }
    vector<vector<int>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    vector<ll> res(n);
    vector<int> sz(n,1), cnt(n);
    auto calc = [&](ll x){
        return x*(x+1)/2;
    };
    // for each color as forbid
    //  for each compo, calc it when block by least-depth node u
    // cnt[c]: till now, #node under some c
    function<void(int,int)> dfs = [&](int u, int p){
        int c = a[u];
        int sub = 0;
        for (int v: g[u])if(v!=p){
            int x = cnt[c];
            dfs(v, u);
            sz[u] += sz[v];
            x = cnt[c]-x;
            // x = delta cnt[c], i.e. in v would block by u's c
            sub += x;
            res[c] += calc(sz[v] - x);
        }
        cnt[c] -= sub;
        cnt[c] += sz[u];
    };
    dfs(0,-1);
    for (int c = 0; c < n; c++) {
        res[c] += calc(n - cnt[c]);
    }
    const ll tot = calc(n);
    for (auto& x: res) {
        cout << tot-x << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
