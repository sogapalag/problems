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
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<vector<int>> evs(n);
    map<int, int> las;
    for (int i = 0; i < n; i++) {
        int x = a[i];
        if (las.find(x) != las.end()) {
            evs[las[x]].emplace_back(i);
        }
        las[x] = i;
    }

    vector<vector<pair<int,int>>> qrs(n);
    for (int i = 0; i < q; i++) {
        int l,r;
        cin >> l >> r;
        l--;
        qrs[l].emplace_back(r, i);
    }
    
    vector<int> res(q);
    SegTree<int> rmi(n, 1e9, 1e9, [](int u, int v){ return min(u,v); });
    for (int l = n-1; l >= 0; l--) {
        for (int r: evs[l]) {
            rmi.assign(r, r-l);
        }
        for (auto& _: qrs[l]) {
            int r,i;
            tie(r,i) = _;
            int x = rmi.query(l, r);
            if (x > 1e8) x = -1;
            res[i] = x;
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
