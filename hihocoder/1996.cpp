#include <bits/stdc++.h>

using namespace std;

#define rep(i) for(int i=0;i<2;i++)
template <typename T=int>
struct Segtree {
    int n; // leaf [n, 2n), view as original [0, n)
    int sz_v;
    const T ID;
    vector<T> v; //tree
    
    Segtree(int _n = 100005) : n(_n), sz_v(n<<1), ID() {
        v.resize(sz_v);
    }
    void init() {// set leaf value
        for (int i = 0; i < n; i++) {
            // v[i+n] = raw[i];
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
    int mat;
    int w[2];

    Node()  {mat=w[0]=w[1]=0;} // DO!! identity
    Node(bool i) {
        mat = 0; w[0]=w[1]=0;
        w[i] = 1;
    }
    Node(const Node& _r) : mat(_r.mat) {
        rep(i) w[i]=_r.w[i];        
    }// DO!! set
    Node& operator = (const Node& _r) {// DO!! set
        mat = _r.mat;
        rep(i) w[i] = _r.w[i];
        return *this;
    }
    Node& operator += (const Node& _r) {// DO!! may not communitative
        mat += _r.mat;
        int x = min(w[1], _r.w[0]);
        mat += x;
        w[0] += _r.w[0] - x;
        w[1] += _r.w[1] - x;
        return *this;
    }
    friend Node operator + (const Node& _lhs, const Node& _rhs) {
        return Node(_lhs) += _rhs; // derive from +=
    }
};

typedef Segtree<Node> Seg;

// each seg, store, #mat, unused #0,#1
void solve() {
    int n; cin >> n;
    Seg s(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        s.update(i, Node(x));
    }

    int q; cin >> q;
    while (q--) {
        int l,r;
        cin >> l >> r;
        int res = s.query(l-1, r).mat;
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
