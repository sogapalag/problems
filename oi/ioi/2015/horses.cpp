#include <bits/stdc++.h>
#include "horses.h"

using namespace std;

template <typename M>
struct SegTree {
    using Op = function<M(const M&, const M&)>;
    M ID; // monoid identity
    Op op; // associative operation
    int N; // 2^lg space, for non-commutative
    vector<M> a;
    
    SegTree(int n, M leaf_default, M _ID, Op _op) : ID(_ID), op(_op) {
        init_space(n);
        fill(a.begin() + N, a.begin() + N + n, leaf_default);
        build();
    }
    SegTree(const vector<M> leaves, M _ID, Op _op) : ID(_ID), op(_op) {
        int n = leaves.size();
        init_space(n);
        copy(leaves.begin(), leaves.end(), a.begin() + N);
        build();
    }
    void init_space(int n) {
        N = 1; while (N < n) N<<=1;
        a.assign(N<<1, ID);
    }
    inline void pull(int i) { a[i] = op(a[i<<1], a[i<<1|1]); }
    void build() { for (int i = N-1; i >= 1; i--) pull(i); }

    void assign(int p, M val) {
        assert(0 <= p && p < N);
        for (a[p += N] = val; p >>= 1;) pull(p);
    }
    M query(int l, int r) const {
        assert(0 <= l && r <= N);
        M resl(ID), resr(ID);
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = op(resl, a[l++]);
            if (r & 1) resr = op(a[--r], resr);
        }
        return op(resl, resr);
    }
    M query_point(int p) const { 
        assert(0 <= p && p < N);
        return a[p + N];
    }
    M query_all() const { return a[1]; }
};
using ll=long long;
const int MOD = 1e9+7; 
inline int mul(int x, int y) {
    //return (ll)x*y % (MOD<<1); // 2*MOD= 0, WA
    ll z = (ll)x*y;
    return z%MOD + (z>=MOD)*MOD;
}
struct M {
    int x;
    double y;
    int z;
    M(){}
    M(int _x, int _y) : x(_x), y(_y), z(mul(x,_y)) {}
    M(int _x, double _y, int _z) : x(_x), y(_y), z(_z) {}
};
SegTree<M> * s;
int n;
int* a;
int* b;

// note ans = max(prod_pref(x) * y)
// note 2^30~1e9, so we only need consider suffix(30 with x>=2)
// one way is impl by set record x>=2.
// below use double modified comp.
// x: reserve >= MOD, for tell suffix
// y: normalized y, i.e. x*y= z
// z: x*y
int init(int n, int a[], int b[]) {
    ::n = n;
    ::a = a;
    ::b = b;
    vector<M> leaves(n);
    for (int i = 0; i < n; i++) {
        leaves[i] = M{a[i],b[i]};
    }
    s = new SegTree<M>(leaves, {1, -1.0, 0},
            [](M u, M v){
            M r;
            r.x = mul(u.x, v.x);
            double y = v.x < MOD ? u.y/v.x : -1.0;
            if (y < v.y) {
                r.y = v.y;
                r.z = mul(u.x, v.z);
            } else {
                r.y = y;
                r.z = u.z;
            }
            return r;
            });
    return s->query_all().z % MOD;
}

int updateX(int i, int x) {
    s->assign(i, M{a[i]=x, b[i]});
    return s->query_all().z % MOD;
}
int updateY(int i, int y) {
    s->assign(i, M{a[i], b[i]=y});
    return s->query_all().z % MOD;
}
