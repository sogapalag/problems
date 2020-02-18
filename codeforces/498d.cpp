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
const int P = 60; //lcm(2..6)
// seg f(t%P) = dt
void solve() {
    int n; cin >> n;
    using M=array<int,P>;
    auto create = [&](int mod){
        M r = {};
        for (int t = 0; t < P; t++) {
            r[t] = 1 + (t%mod == 0); 
        }
        return r;
    };
    M B[7];
    for (int i = 2; i <= 6; i++) {
        B[i] = create(i);
    }
    vector<M> a(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i] = B[x];
    }
    SegTree<M> s (a, M{},
            [](M u, M v){
                M r = {};
                for (int t = 0; t < P; t++) {
                    int dt = u[t];
                    r[t] = dt + v[(t+dt)%P];
                }
                return r;
            }
            );
    
    int q; cin >> q;
    while (q--) {
        char op; int x,y;
        cin >> op >> x >> y;
        if (op == 'A') {
            x--; y--;
            cout << s.query(x, y)[0] << '\n';
        } else {
            x--;
            s.assign(x, B[y]);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
