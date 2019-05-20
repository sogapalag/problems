#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
struct Segtree {
    int n; // leaf [n, 2n), view as original [0, n)
    int sz_v;
    const T ID;
    vector<T> v; //tree
    
    Segtree(int _n = 100005) : n(_n), sz_v(n<<1), ID() {
        v.resize(sz_v);
    }
    void init(vector<int>& raw) {// set leaf value
        for (int i = 0; i < n; i++) {
            v[i+n].x = raw[i];
            v[i+n].id = i;
        }
        build();
    }
    void build() {
        for (int i = n-1; i >= 0; i--) {
            v[i] = v[i<<1] + v[i<<1|1];
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
};

struct Node {// monoid
    int x;
    int id;
    Node(int _=0) : x(0x3f3f3f3f), id(-1) {} // DO!! identity
    Node(const Node& _r) : x(_r.x), id(_r.id) {}// DO!! set
    Node& operator = (const Node& _r) {// DO!! set
        x = _r.x; id = _r.id;
        return *this;
    }
    Node& operator += (const Node& _r) {// DO!! may not communitative
        if (_r.x < x) {
            x = _r.x; id = _r.id;
        }
        return *this;
    }
    friend Node operator + (const Node& _lhs, const Node& _rhs) {
        return Node(_lhs) += _rhs; // derive from +=
    }
};

typedef Segtree<Node> Seg;

// LCA -> RMQ
// imagine surround the tree, a euler-path(dfs preorder)
// https://www.topcoder.com/community/competitive-programming/tutorials/range-minimum-query-and-lowest-common-ancestor/
void solve() {
    int n; cin >> n;
    vector<int> g[1005];
    for (int i = 1; i <= n; i++) {
        int k; cin >> k;
        while (k--) {
            int x; cin >> x;
            g[i].emplace_back(x);
        }
    }
    vector<int> e(2*n - 1);
    vector<int> h(2*n - 1);
    vector<int> f(n+1);
    int cnt = 0;
    function<void(int, int)> dfs = [&](int u, int d){
        f[u] = cnt;
        e[cnt] = u;
        h[cnt++] = d;
        for (int v: g[u]) {
            dfs(v, d+1);
            e[cnt] = u;
            h[cnt++] = d;
        }
    };
    dfs(1, 0);
    Seg seg(2*n-1); seg.init(h);
    int q; cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        int u = f[x], v = f[y];
        if (u > v) swap(u, v);
        cout << e[seg.query(u, v+1).id] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case " << i << ":\n";
        solve();
    }
    cout << endl;
}
