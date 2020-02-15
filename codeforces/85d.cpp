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

template <typename T=int>
struct Compress {
    map<T, int> id;
    vector<T> num;

    Compress(vector<T> v) {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        num = v;
        for (int i = 0; i < (int)num.size(); i++) {
            id[num[i]] = i;
        }
    }

    inline int get_id(T x) {
        assert(id.count(x));
        return id[x];
    }
    inline T get_num(int i) {
        assert(0 <= i && i < num.size());
        return num[i];
    }
};
void solve() {
    int q; cin >> q;
    vector<int> qrs(q);
    vector<int> Xs;
    for (int _ = 0; _ < q; _++) {
        string s; int x = 0;
        cin >> s;
        if (s[0]!='s') {
            cin >> x;
            Xs.push_back(x);
            if (s[0]=='d') x*=-1;
        }
        qrs[_] = x;
    }
    Compress<> cx(Xs);
using ll=long long ;
    using M = array<ll,6>;
    int n = cx.num.size();
    SegTree<M> sum (n, {0,0,0,0,0,0}, {0,0,0,0,0,0},
            [](M u, M v){
            M r = u;
            for (int i = 0; i < 5; i++) {
                r[(i + u[5])%5] += v[i];
            }
            r[5] += v[5];
            return r;
            }
            );
    for (auto& x: qrs) {
        if (x == 0) {
            ll res = sum.query_all()[2];
            cout << res << '\n';
        } else if (x > 0) {
            int i = cx.get_id(x);
            sum.assign(i, {x,0,0,0,0,1});
        } else {
            int i = cx.get_id(-x);
            sum.assign(i, {0,0,0,0,0,0});
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
