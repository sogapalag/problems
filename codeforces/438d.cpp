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
using ll=long long;
// the key insight, whenever x>p, x%p loss >half x
// and op2, a never inc. and op3 inc only 1 number, i.e(log)
// so brute force dec range-max
void solve() {
    int n,q;
    cin >> n >> q;
    
    struct Node {
        ll sum;
        int mx, id;
        Node() {}
        Node(ll _sum, int _mx, int _id) : sum(_sum), mx(_mx), id(_id) {}
        bool operator<(const Node& _oth) const {
            return mx < _oth.mx;
        }
    };
    vector<Node> a(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i] = {x, x, i};
    }
    SegTree<Node> s (a, {0, -1, -1}, [](auto u, auto v){
            if (u < v) return Node{u.sum + v.sum, v.mx, v.id};
            else return Node{u.sum + v.sum, u.mx, u.id};
            });

    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int l,r;
            cin >> l >> r; l--;
            cout << s.query(l,r).sum << '\n';
        } else if (op == 2){
            int l,r,p;
            cin >> l >> r >> p; l--;
            while (true) {
                auto nd = s.query(l, r);
                if (nd.mx >= p) {
                    int i = nd.id;
                    int x = nd.mx%p;
                    s.assign(i, {x,x,i});
                }else break;
            }
        } else {
            int i,x;
            cin >> i >> x; i--;
            s.assign(i, {x,x,i});
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
