#include <bits/stdc++.h>

using namespace std;
using ll=long long;

template <typename T=int>
struct Segtree {
    int n; // leaf [n, 2n), view as original [0, n)
    int sz_v;
    const T ID;
    vector<T> v; //tree
    
    Segtree(int _n = 100005) : n(_n), sz_v(n<<1), ID() {
        v.assign(sz_v, ID);
    }
    void init() {// set leaf value
        for (int i = 0; i < n; i++) {
            // v[i+n] = raw[i];
        }
        build();
    }
    void build() {
        for (int i = n-1; i > 0; i--) {
            v[i] = v[i<<1] + v[i<<1|1];
        }
    }
    inline void update(int p, T val) {
        assert(p>=0);
        for (v[p += n] += val; p >>= 1;) { // change to  min upd
            v[p] = v[p<<1] + v[p<<1|1];
        }
    }
    inline T query(int l, int r) {
        T resl(ID), resr(ID);
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) { resl = resl + v[l++]; }
            if (r & 1) { resr = v[--r] + resr; }
        }
        return resl + resr;
    }
    // Note only when range-assign, single-access not interfere. e.g max
    //inline void update(int l, int r, T val) {
    //    for (l += n, r += n; l < r; l >>= 1, r >>= 1){
    //        if (l & 1) { v[l++] = val; }
    //        if (r & 1) { v[--r] = val; }
    //    }
    //}
    //inline T query(int p){
    //    T res(ID);
    //    for (p += n; p > 0; p >>= 1) { res += v[p]; }
    //    return res;
    //}
};

struct Node {// monoid
    ll x;
    Node() : x(0x3f3f3f3f3f3f3f3f) {} // DO!! identity
    Node(ll _x) : x(_x) {}
    Node(const Node& _r) : x(_r.x) {}// DO!! set
    Node& operator = (const Node& _r) {// DO!! set
        x = _r.x;
        return *this;
    }
    Node& operator += (const Node& _r) {// DO!! may not communitative
        x = min(x, _r.x);
        return *this;
    }
    friend Node operator + (const Node& _lhs, const Node& _rhs) {
        return Node(_lhs) += _rhs; // derive from +=
    }
};

typedef Segtree<Node> Seg;

// obvious [l,r] use at most once
//  and if use must to r, since any future overlap r can achieve as (<r)
//
// editorial method, construct graph with
// l->r, c 
// and i+1 -> i, 0
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> g(n+1);
    for (int _ = 0; _ < m; _++) {
        int l,r,c;
        cin >> l >> r >> c;
        g[r].emplace_back(l,c);
    }
    Seg s(n+1);
    s.update(1, Node(0));
    //cout << s.query(1, 2).x << "\n";
    for (int r = 2; r <= n; r++) {
        for (auto& p: g[r]) {
            int l,c;
            tie(l,c) = p;
            auto mi = s.query(l, r);
            mi.x += c;
            //cout << mi.x << "\n";
            s.update(r, mi);
        }
    }
    ll res = s.query(n, n+1).x;
    if (res > 1e16) res = -1;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
