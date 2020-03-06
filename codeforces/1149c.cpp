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

// first note depth = pref sum of  +1, -1 ..
// note dist = d(u)+d(v) - 2*d(lca) 
// what's lca? one might thought first outter match '()', i.e. (_z (_u) (_v) )
// but there is a easy way to get d(lca) := min(sum[u..v]), i.e. we care between is enough.
//    since one can imagine the dfs-tour, it must return')' lca, at that time the d is smallest.
// also note that we don't need focusing on '(' only. we can relax it only care sum.(since won't be exceed)
// now problem become
// find triplet(i<j<k) s.t. d[i] - 2d[j] + d[k] is maximum.
// use segtree maintain info for possible merge. i.e. i,j,k in left or right.
//   and careful right need plus left.sum * some coeff. (also, one see 1-2+1=0, i.e. absolute depth is irrelevant)
void solve() {
    int n, q;
    cin >> n >> q;
    string s; cin >> s;
    const int NINF = -1e8; 
    struct M {
        int sum;
        int a, B, aB, Ba, aBa;
        M()
            : sum(0)
            , a(NINF)
            , B(NINF)
            , aB(NINF)
            , Ba(NINF)
            , aBa(NINF)
        {}
        M(int x)
            : sum(x)
            , a(x)
            , B(-2*x)
            , aB(NINF)
            , Ba(NINF)
            , aBa(NINF)
        {}
        M(int _sum, int _a, int _B, int _aB, int _Ba, int _aBa)
            : sum(_sum)
            , a(_a)
            , B(_B)
            , aB(_aB)
            , Ba(_Ba)
            , aBa(_aBa)
        {}
    };
    //s = "(" + s + ")"; n++;
    vector<M> leaves(2*n);
    for (int i = 0; i < 2*n; i++) {
        int x = s[i]=='(' ? 1 : -1;
        leaves[i] = M(x);
    }
    SegTree<M> seg(leaves, M(), [](M u, M v){
            M r;
            r.aBa = max({u.aBa
                    , v.aBa
                    , u.a + v.Ba - u.sum
                    , u.aB + v.a + u.sum});
            r.aB = max({u.aB
                    , v.aB - u.sum
                    , u.a + v.B - 2*u.sum});
            r.Ba = max({u.Ba
                    , v.Ba - u.sum
                    , u.B + v.a + u.sum});
            r.B = max({u.B
                    , v.B - 2*u.sum});
            r.a = max({u.a
                    , v.a + u.sum});
            r.sum = u.sum + v.sum;
            return r;
            });

    int res = seg.query_all().aBa;
    cout << res << '\n';
    while (q--) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        if (s[x] != s[y]) {
            swap(s[x], s[y]);
            int sx = s[x]=='('?1:-1;
            int sy = s[y]=='('?1:-1;
            seg.assign(x, M(sx));
            seg.assign(y, M(sy));
        }
        res = seg.query_all().aBa;
        cout << res << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
