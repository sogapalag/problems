#include <bits/stdc++.h>
using namespace std;


/////////////////////////////////
// root is 1, perfect tree; hint: n is not power of 2 also right.
// raw data(leaf) in a[n,...2*n)
// i: parent; 2*i, 2*i+1 children.
//
// classic update-one, query range

// SNIPPETS_START segtree
template <typename T=int>
struct Segtree {
    int n; // leaf [n, 2n), view as original [0, n)
    int sz_v;
    const T ID;
    vector<T> v; //tree
    
    Segtree(int _n = 100005) : n(_n), sz_v(n<<1) {
        ID = T(); // set id
        v.resize(sz_v);
        init(); build();
    }
    void init() {// set leaf value
        for (int i = 0; i < n; i++) {
            // v[i+n] = raw[i];
        }
    }
    void build() {
        for (int i = n-1; i >= 0; i--) {
            v[i] = v[i<<1] + v[i<<1|1];
        }
    }
    inline void update(int p, T val) {
        assert(p>=0);
        for (v[p += n] = val; p > 1; p >>= 1) {
            v[p>>1] = v[p] + v[p^1];
        }
    }
    inline T query(int l, int r) {
        T resl(ID), resr(ID);
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) { resl = v[l++] + resl; }
            if (r & 1) { resr = resr + v[--r]; }
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
    int x;
    Node(int _=0) : x(-0x3f3f3f3f) {} // write your own identity
    Node(const Node& _r) : x(_r.x) {}// write your own
    Node& operator = (const Node& _r) {
        x = _r.x; // write your own
        return *this;
    }
    Node& operator += (const Node& _r) {
        x = max(x, _r.x); // write your own  !! may not communitative
        return *this;
    }
    friend Node operator + (const Node& _lhs, const Node& _rhs) {
        return Node(_lhs) += _rhs; // derive from +=
    }
};

typedef Segtree<Node> Seg;
// SNIPPETS_END
