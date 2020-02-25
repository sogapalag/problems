#include <bits/stdc++.h>

using namespace std;
using ll=long long;
struct Dsu {
    int n;
    vector<int> p;
    vector<int> r;
    
    Dsu(int _n) { n = _n; p.resize(n); r.resize(n); init(); }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
            r[i] = 1;
        }
    }
    inline int find(int x) {
        return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline bool join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (r[x] < r[y]) swap(x, y);
        p[y] = x; r[x] += r[y];
        return true;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
    inline int size(int x) {
        return r[find(x)];
    }
};

void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    vector<int> U(n-1),V(n-1),W(n-1);
    for (int i = 0; i < n-1; i++) {
        cin >> U[i] >> V[i] >> W[i];
        --U[i]; --V[i];
        g[U[i]].push_back(V[i]);
        g[V[i]].push_back(U[i]);
    }
    vector<int> depth(n);
    function<void(int,int)> dfs = [&](int u, int p){
        for (int v:g[u])if(v!=p){
            depth[v] = depth[u] + 1;
            dfs(v,u);
        }
    };
    dfs(0, -1);
    vector<int> token(n-1);
    for (int i = 0; i < n-1; i++) {
        if (depth[U[i]] < depth[V[i]]) swap(U[i], V[i]);
        token[i] = depth[U[i]];
    }
    vector<int> id(n-1);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](auto& u, auto& v){
        // key is break tie with depth, then we can know at least one side(down) size
        return W[u] < W[v] || (W[u] == W[v] && token[u] > token[v]);
    });

    Dsu d(n);
    vector<ll> res(n-1);
    int _ = 0;
    while (_ < n-1) {
        int __ = _;
        int i = id[_];
        while (_ < n-1 && W[id[_]] == W[i]) {
            int j = id[_];
            res[j] = d.size(U[j]);
            d.join(U[j], V[j]);
            _++;
        }
        while (__ < _) {
            i = id[__++];
            int sz = d.size(U[i]);
            res[i] = (sz - res[i]) * 1ll * res[i];
        }
    }
    ll mx = *max_element(res.begin(), res.end());
    vector<int> ans;
    for (int i = 0; i < n-1; i++) {
        if (res[i] == mx) {
            ans.push_back(i);
        }
    }
    cout << mx*2 << ' ' << ans.size() << "\n";
    for (auto& x: ans) {
        cout << x+1 << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
