#include <bits/stdc++.h>

using namespace std;
using ll=long long;
template <typename T=int>
struct Rmq {
    vector<T> raw;
    static const int LOG = 19; // 20;
    int k;
    int n;
    vector<int> st[LOG];
    Rmq(vector<T> _v) { // pass in vec[0, n)
        raw = _v;
        n = raw.size();
        k = 32 - __builtin_clz(n);
        for (int j = 0; j < k; j++) {
            st[j].resize(n);
        }
        build();
    }
    inline int comp(int x, int y) { // DO! > max
        return raw[x] < raw[y] ? x : y;
    }
    void build() {
        for (int i = 0; i < n; i++) {
            st[0][i] = i;
        }
        for (int j = 1; j < k; j++) {
            for (int i = 0; i + (1<<j) <= n; i++) {
                st[j][i] = comp(st[j-1][i], st[j-1][i + (1<<(j-1))]);
            }
        }
    }
    // [l, r)
    inline int query_id(int l, int r) {
        assert(0 <= l && l < r && r <= n);
        int j = 31 - __builtin_clz(r - l);
        return comp(st[j][l], st[j][r - (1<<j)]);
    }
    inline T query(int l, int r) {
        return raw[query_id(l, r)];
    }
};

struct Dsu {
    int n;
    vector<int> p;
    
    Dsu(int _n) { n = _n; p.resize(n); init(); }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
    }
    inline int find(int x) {
        return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline bool join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        p[y] = x; return true;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
};

struct Edge {
    int x, y;
    ll cost;
    Edge() {}
    Edge(int _x, int _y, ll _cost) : x(_x), y(_y), cost(_cost) {}
    bool operator<(const Edge& _oth) const {
        return cost < _oth.cost;
    }
};

// es between [l,m) [m,r), end must i or j. otherwise (x,j)(y,i)(i,j) all < (x,y) form cycle, so (x,y) cannot be in MST. thus total O(n log n) candidates
//
// another method O(n) candidates, for fixed j, A_i < A_j, i<j, min-cost A_i-iD only be candidate. similar proof. omit
void solve() {
    int n; ll D;
    cin >> n >> D;
    vector<ll> a(n), L(n), R(n);
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        a[i] = x;
        L[i] = x - i*D;
        R[i] = x + i*D;
    }
    Rmq<ll> mL(L), mR(R);
    
    vector<Edge> es;
    function<void(int,int)> cut = [&](int l, int r){
        if (r-l <= 1) return;
        int m = (r+l)/2;
        int i = mL.query_id(l, m);
        for (int k = m; k < r; k++) {
            es.emplace_back(i,k, R[k]+L[i]);
        }
        int j = mR.query_id(m, r);
        for (int k = l; k < m; k++) {
            es.emplace_back(j,k, L[k]+R[j]);
        }
        cut(l, m);
        cut(m, r);
    };
    cut(0, n);
    sort(es.begin(), es.end());
    
    Dsu d(n);
    ll res = 0;
    for (auto& e: es) {
        if (!d.check(e.x, e.y)) {
            res += e.cost;
            d.join(e.x, e.y);
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
