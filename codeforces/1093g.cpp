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

// build 2^k segtree, candi is sum of dual mask 
void solve() {
    int n,k;
    cin >> n >> k;
    const int MSK = 1<<k; 
    struct Node {
        vector<int> a, m; // a actual don't need
        Node(int k) { a.assign(k, -1e7); m.assign(1<<k, -1e8); }
        Node(int k, vector<int> _a) : a(_a) {
            m.resize(1<<k);
            for (int msk = 0; msk < 1<<k; msk++) {
                for (int i = 0; i < k; i++) {
                    if (msk>>i&1) m[msk]-=a[i];
                    else m[msk]+=a[i];
                }
            }
        }
    };
    vector<Node> a;
    for (int i = 0; i < n; i++) {
        vector<int> t;
        for (int _ = 0; _ < k; _++) {
            int x; cin >> x;
            t.push_back(x);
        }
        a.emplace_back(k, t);
    }
    SegTree<Node> s (a, {k},
            [&](Node u, Node v){
                Node r(k);
                for (int msk = 0; msk < MSK; msk++) {
                    r.m[msk] = max(u.m[msk], v.m[msk]);
                }
                return r;
            }
            );

    int q; cin >> q;
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int i; vector<int> t;
            cin >> i; i--;
            for (int _ = 0; _ < k; _++) {
                int x; cin >> x; t.push_back(x);
            }
            s.assign(i, Node{k, t});
        } else {
            int l, r;
            cin >> l >> r;
            l--;
            auto m = s.query(l, r).m;
            int res = 0;
            for (int msk = 0; msk < MSK; msk++) {
                res = max(res, m[msk] + m[msk^(MSK-1)]);
            }
            cout << res << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
