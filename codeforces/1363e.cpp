#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n; cin >> n;
    vector<int> a(n),b(n),c(n);
    int sb = 0, sc = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i] >> c[i];
        sb += b[i];
        sc += c[i];
    }
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
        int x,y;
        cin >> x >> y;
        --x;--y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    if (sb != sc) {
        cout << -1; return;
    }

    vector<array<int,2>> s(n);
    ll res = 0;
    function<void(int,int)> dfs = [&](int u, int p){
        for (int v: g[u])if(v!=p){
            a[v] = min(a[v], a[u]); // best
            dfs(v, u);
            s[u][0] += s[v][0];
            s[u][1] += s[v][1];
        }
        if (b[u]!=c[u]) s[u][b[u]]++;
        // greedy pair up
        int x = min(s[u][0], s[u][1]);
        s[u][0] -= x; s[u][1] -= x;
        res += x * 2ll * a[u];
    };
    dfs(0,-1);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
