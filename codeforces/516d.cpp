#include <bits/stdc++.h>

using namespace std;

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
    int size(int x) {
        return r[find(x)];
    }
    void dec(int x) {
        --r[find(x)];
    }
};
using ll=long long;
// first prep arm
// the problem ask max |scc| s.t diff{arm} <= l
// the key is note arm has a structure, by diameter property
//   that we root at midpoint of diameter, then arm[pa[v]] <= arm[v], for any v
// then we can apply dfs with stack, but easy-impl can by dsu with two-pointer.
void solve() {
    int n; cin >> n;
    vector<vector<pair<int,int>>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x,y,z;
        cin >> x >> y >> z;
        x--;y--;
        g[x].emplace_back(y, z);
        g[y].emplace_back(x, z);
    }

    vector<int> pa(n, -1);
    vector<ll> arm(n);
    function<void(int,int,ll)> dfs = [&](int u, int p, ll depth) {
        pa[u] = p;
        arm[u] = max(arm[u], depth);
        for (auto [v,w]:g[u])if(v!=p){
            dfs(v,u, depth + w);
        }
    };
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);

    dfs(0,-1,0);
    int r = *max_element(id.begin(), id.end(), [&](int i, int j){
            return arm[i] < arm[j];
            });
    dfs(r,-1,0);
    r = *max_element(id.begin(), id.end(), [&](int i, int j){
            return arm[i] < arm[j];
            });
    dfs(r,-1,0);

    sort(id.begin(), id.end(), [&](auto& u, auto& v){
        return arm[u] > arm[v];
    });
    r = id.back(); // mid-point
    dfs(r,-1,0);

    int q; cin >> q;
    while (q--) {
        Dsu d(n);
        ll L; cin >> L;
        int res = 0;
        for (int _ = 0, __ = 0; _ < n; _++) {
            int u = id[_];
            for (auto [v,_w]: g[u])if(v!=pa[u]){
                d.join(u, v);
            }
            while (__ < _) {
                int x = id[__];
                if (arm[x] <= arm[u] + L) break;
                // exclude, we don't have to actually disconnect it, dec its size by one.
                d.dec(x); __++;
            }
            res = max(res, d.size(u));
        }
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
