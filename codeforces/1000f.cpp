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

void solve() {
    int n; cin >> n;
    SegTree<int> rmi (n, 1e9, 1e9, [](int u, int v){ return min(u,v); });
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    
    const int N = 5e5+10; 
    vector<int> las(N);
    for (int i = 1; i < N; i++) {
        las[i] = -i;// thus we don't store id in rmi
    }

    vector<vector<pair<int,int>>> evs(n+1);
    int q; cin >> q;
    for (int _ = 0; _ < q; _++) {
        int l, r;
        cin >> l >> r;
        l--;
        evs[r].emplace_back(l, _);
    }
    vector<int> res(q);
    for (int r = 1; r <= n; r++) {
        int x = a[r-1];
        rmi.assign(r-1, las[x]);
        // reset las
        if (las[x] >= 0) {
            rmi.assign(las[x], 1e9);
        }
        las[x] = r-1;
        for (auto& _: evs[r]) {
            int l,i;
            tie(l,i) = _;
            int x = rmi.query(l, r);
            if (x < l) {
                if (x < 0) res[i] = -x;
                else res[i] = a[x];
            } else {
                res[i] = 0;
            }
        }
    }
    for (auto& x: res) {
        cout << x << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
