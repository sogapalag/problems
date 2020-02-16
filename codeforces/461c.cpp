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
    void update(int p, M val) {
        assert(0 <= p && p < N);
        p += N;
        for (a[p] = op(a[p], val); p >>= 1;) pull(p);
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

// key: paper length dec <=n, brute force update,
//   as long as, if x > mid, we fold other-side, keep a tag the paper reversed
void solve() {
    int n,q;
    cin >> n >> q;
    SegTree<int> paper(n, 1, 0, [](int u, int v){ return u+v; });
    int L = 0, R = n; bool rev = false;
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int x; cin >> x;
            if (x <= (R-L)/2) {
                if (rev) {
                    for (int i = 0; i < x; i++) {
                        paper.update(R-2*x+i, paper.query_point(R-i-1));
                    }
                    R -= x;
                } else {
                    for (int i = 0; i < x; i++) {
                        paper.update(L+2*x-i-1, paper.query_point(L+i));
                    }
                    L += x;
                }
            } else {
                x = R-L - x;
                if (rev) {
                    for (int i = 0; i < x; i++) {
                        paper.update(L+2*x-i-1, paper.query_point(L+i));
                    }
                    L += x;
                    rev = false;
                } else {
                    for (int i = 0; i < x; i++) {
                        paper.update(R-2*x+i, paper.query_point(R-i-1));
                    }
                    R -= x;
                    rev = true;
                }
            }
        } else {
            int l,r;
            cin >> l >> r;
            if (rev) {
                cout << paper.query(R-r, R-l) << '\n';
            } else {
                cout << paper.query(L+l, L+r) << '\n';
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
