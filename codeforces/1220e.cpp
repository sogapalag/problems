#include <bits/stdc++.h>

using namespace std;
using ll=long long ;


// node : in cycle or in the path to cycle. can always be taken, s->cycle -> s
// remain tree, find max path to leaf.
//
// we don't need actually merge cycle nodes. just use [bool], since if v in_c then u too.
void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<vector<int>> g(n);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    int s; cin >> s;
    s--;

    vector<bool> trk(n,false), in_c(n,false);
    vector<ll> arm(n, 0);
    function<void(int,int)> dfs = [&](int u, int p){
        trk[u] = true;
        ll mx = 0;
        for (int v: g[u])if(v!=p) {
            if (trk[v]) {
                in_c[u] = true; // cycle
            } else {
                dfs(v, u);
                in_c[u] = in_c[u] || in_c[v]; // in path to cycle
                mx = max(mx, arm[v]);
            }
        }
        arm[u] = mx;
        if (!in_c[u]) arm[u] += a[u];
    };
    dfs(s, -1);
    ll res = arm[s];
    for (int i = 0; i < n; i++) {
        if (in_c[i]) res += a[i];
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
