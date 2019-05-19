#include <bits/stdc++.h>

using namespace std;

#define dbg(x) cerr<<#x<<" = "<<(x)<<endl;

template <typename T=int>
struct Segtree {
    int n; // leaf [n, 2n), view as original [0, n)
    int sz_v;
    const T ID;
    vector<T> v; //tree
    
    Segtree(int _n = 100005) : n(_n), sz_v(n<<1), ID(){
        //ID = T(0); // set id
        v.resize(sz_v);
    }
    void init(vector<int> & a) {// set leaf value
        for (int i = 0; i < n; i++) {
            v[n+i].lx = v[n+i].rx = v[n+i].mx = v[n+i].sm = a[i];
        }
        build();
    }
    void build() {
        for (int i = n-1; i >= 0; i--) {
            v[i] = v[i<<1] + v[i<<1|1];
        }
    }
    inline void update(int p, T val) {
        assert(p>=0);
        for (v[p += n] = val; p >>= 1;) {
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
};

const int INF = 0x3f3f3f3f;
struct Node {// monoid
    int lx, rx, mx, sm;

    Node(int _=0) : lx(-INF), rx(-INF), mx(-INF), sm(0) {} // write your own identity
    Node(const Node& _r) : lx(_r.lx), rx(_r.rx), mx(_r.mx), sm(_r.sm) {}// write your own
    Node& operator = (const Node& _r) {
        lx = _r.lx, rx = _r.rx, mx = _r.mx, sm = _r.sm; // write your own
        return *this;
    }
    Node& operator += (const Node& _r) { // write your own  !! may not communitative
        int tlx = max(lx, sm + _r.lx);
        int trx = max(_r.rx, _r.sm + rx);
        int tmx = max({mx, _r.mx, rx + _r.lx});
        int tsm = sm + _r.sm;
        lx = tlx, rx = trx, mx = tmx, sm = tsm;
        return *this;
    }
    friend Node operator + (const Node& _lhs, const Node& _rhs) {
        return Node(_lhs) += _rhs; // derive from +=
    }
};

typedef Segtree<Node> Seg;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    Seg seg(n);
    seg.init(a);
    int m; cin >> m;
    while (m--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op) {
            cout << seg.query(x-1, y).mx << "\n";
        } else {
            Node nd; nd.lx=nd.rx=nd.mx=nd.sm=y;
            seg.update(x-1, nd);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
