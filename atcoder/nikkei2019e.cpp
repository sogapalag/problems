#include <bits/stdc++.h>

using namespace std;

using ll=long long;
struct Dsu {
    int n;
    vector<int> p;
    vector<ll> r; // for weight now
    vector<int> cnt; // #potential edges
    
    Dsu(int _n) { n = _n; p.resize(n); r.resize(n); init(); }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
            r[i] = 1;
        }
        cnt.assign(n, 0);
    }
    inline int find(int x) {
        return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline bool join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (r[x] < r[y]) swap(x, y);
        p[y] = x; r[x] += r[y];
        cnt[x] += cnt[y];
        return true;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
    ll weight(int x) {
        return r[find(x)];
    }
    void add_unused_edge(int x) {
        cnt[find(x)]++;
    }
    int use_edge(int x) {
        int res = cnt[find(x)];
        cnt[find(x)] = 0;
        return res;
    }
};

struct Edge {
    int x, y, z;
    Edge() {}
    Edge(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
    bool operator<(const Edge& _oth) const {
        return z < _oth.z;
    }
};

// lemma, if e in(not deleted) then \A e'<e connected in component also in.
//
// 
// so sort, we always merge, store #potential edges, while valid add # in.
void solve() {
    int n,m;
    cin >> n >> m;
    Dsu d(n);
    for (int i = 0; i < n; i++) {
        cin >> d.r[i];
    }
    vector<Edge> es(m);
    for (int i = 0; i < m; i++) {
        int x,y,z;
        cin >> x >> y >> z;
        x--;y--;
        es[i] = {x,y,z};
    }
    sort(es.begin(), es.end());
    int res = 0;
    for (auto& e: es) {
        d.join(e.x,e.y);
        d.add_unused_edge(e.x);
        if (d.weight(e.x) >= e.z) {
            res += d.use_edge(e.x);
        }
    }
    res = m-res;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
