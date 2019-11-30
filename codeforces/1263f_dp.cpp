#include <bits/stdc++.h>

using namespace std;

int D;
vector<tuple<int,int,int>> segs;

void create_segs() {
    int n; cin >> n;
    vector<int> sz(n, 1), device(n, -1), l(n, D), r(n, 0);
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
        int p; cin >> p; p--;
        g[p].emplace_back(i);
    }
    for (int i = 0; i < D; i++) {
        int x; cin >> x; x--;
        device[x] = i;
    }
    function<void(int)> dfs = [&](int u){
        if (device[u] != -1) {
            l[u] = device[u];
            r[u] = device[u]+1;
        }
        for (int v: g[u]) {
            dfs(v);
            sz[u] += sz[v];
            l[u] = min(l[u], l[v]);
            r[u] = max(r[u], r[v]);
        }
        segs.emplace_back(l[u], r[u], sz[u] - (u==0));
    };
    dfs(0);
}

// problem ensure leaf consective in-order
// seg means give up subtree of u, i.e. range(l,r). with profit.
// note in dp, dp[l]+v ensure we don't choose overlap segs.
// finally optimal is each device is powered by only one side, aka we give up exactly one whole seg.
void solve() {
    cin >> D;
    create_segs();
    create_segs();
    sort(segs.begin(), segs.end());
    vector<int> dp(D+1, 0);
    for (auto& s: segs) {
        int l,r,v;
        tie(l,r,v) = s;
        dp[r] = max(dp[r], dp[l] + v);
    }
    cout << dp[D];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
