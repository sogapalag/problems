#include <bits/stdc++.h>

using namespace std;
using pi=pair<int, int>;
using ll=long long;

struct Dsu {
    using pi=pair<int, int>;
    int n;
    vector<int> p;
    vector<int> r;
    vector<int> s;
    vector<pi> histo;
    ll delta = 0;

    Dsu(int _n) { n = _n; p.resize(n); r.resize(n); s.resize(n); init(); }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
            if (i&1) s[i] = 1;
            else r[i] = 1;
        }
    }
    inline int find(int x) { // don't compress path
        while (x != p[x]) x = p[x];
        return x;
        //return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline int join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return 0;
        if (r[x] < r[y]) swap(x, y);
        histo.emplace_back(x, y);
        delta -= prod(x) + prod(y);
        p[y] = x; r[x] += r[y];
        s[x] += s[y];
        delta += prod(x);
        return 1;
    }
    inline int join(pi e) {
        return join(e.first, e.second);
    }
    void roll_back() {
        int x,y;
        tie(x,y) = histo.back(); histo.pop_back();
        delta -= prod(x);
        r[x] -= r[y]; p[y] = y;
        s[x] -= s[y];
        delta += prod(x) + prod(y);
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
    inline bool check(pi e) {
        return check(e.first, e.second);
    }
    ll prod(int x) {
        x = find(x);
        return r[x]*1ll*s[x];
    }
};

const int N = 1<<19; 
Dsu d(N<<1);
vector<pi> a[N<<1];
ll res[N];
void add(int l, int r, pi& p) {
    for (l += N, r += N; l < r; l>>=1, r>>=1) {
        if (l&1) a[l++].push_back(p);
        if (r&1) a[--r].push_back(p);
    }
}
void dfs(int u){
    int did = 0;
    for (auto& p: a[u]) {
        did += d.join(p); // some might skip, so no need roll_back, if don't track did, invalid pointer
    }
    if (u >= N) {
        res[u-N] = d.delta;
    } else {
        dfs(u<<1); dfs(u<<1|1);
    }
    while (did--) {
        d.roll_back();
    }
}

// first note each compo (finally generated) will be rect, so need track #x, #y, size = #x*#y
// to support delete, divide time as segment, dfs.
void solve() {
    int n; cin >> n;
    map<pi,int> pos;
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        x = x*2; y = y*2+1;
        pi p = {x,y};
        if (pos.count(p)) {
            add(pos[p], i, p);
            pos.erase(p);
        } else {
            pos[p] = i;
        }
    }
    for (auto& _: pos) {
        pi p = _.first;
        add(_.second, n, p);
    }
    dfs(1);

    for (int i = 0; i < n; i++) {
        cout << res[i] << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
