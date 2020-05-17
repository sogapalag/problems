#include <bits/stdc++.h>

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
        N = 1; while (N < n) N <<= 1;
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
struct M {
    ll len, s, f;
    M() {len=s=f=0;}
    M(ll _len, ll _s, ll _f) : len(_len), s(_s), f(_f) {}
};
// s= 1 -2 3 -4 ..
// f= 1 -1 1 -1 ..
void solve() {
    int n,q;
    cin >> n >> q;
    vector<M> leaves(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        leaves[i] = M{1,x,x};
    }
    SegTree<M> seg(leaves, {},
            [](M u, M v){
                M r;
                r.len = u.len+v.len;
                if (u.len&1) {
                    r.s = u.s - (v.s+v.f*u.len);
                    r.f = u.f - v.f;
                } else {
                    r.s = u.s + v.s + v.f*u.len;
                    r.f = u.f + v.f;
                }
                return r;
            });
    ll tot = 0;
    while (q--) {
        char op; int x,y;
        cin >> op >> x >> y;
        --x;
        if (op=='U') {
            seg.assign(x, M{1,y,y});
        } else {
            tot += seg.query(x, y).s;
        }
    }
    cout << tot << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
