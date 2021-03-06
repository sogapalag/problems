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
        //N = 1; while (N < n) N<<=1;
        N = n;
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
void solve() {
    int n, lim, m;
    cin >> n >> lim >> m;
    vector<SegTree<ll>> s;
    // 4096*2, 2^l MLE, use simple
    for (int i = 0; i <= m; i++) {
        s.emplace_back(n+1, -1e18, -1e18, [](ll u, ll v){ return max(u,v); });
    }
    s[0].assign(0, 0);
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        int l = max(0, i - lim);
        for (int j = m; j >= 1; j--) {
            s[j].assign(i, s[j-1].query(l, i) + x);
        }
    }

    ll res = -1;
    for (int i = n-lim+1; i <= n; i++) {
        res = max(res, s[m].query(i, n+1));
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
