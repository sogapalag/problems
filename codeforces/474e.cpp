#include <bits/stdc++.h>

using namespace std;
using ll=long long;

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
        for (a[p] = max(a[p], val); p >>= 1;) pull(p);
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
    int n; ll D;
    cin >> n >> D;
    vector<ll> a(n), Xs;
    for (auto& x: a) {
        cin >> x;
        Xs.push_back(x - D);
        Xs.push_back(x);
        Xs.push_back(x + D);
    }
    Compress<ll> cx(Xs);
    
    using pi=pair<int,int>;
    int m = cx.num.size();
    SegTree<pi> dp (m, {0,-1}, {0,-1}, [](pi u, pi v){ return max(u,v); });

    vector<int> pre(n,-1);
    for (int i = 0; i < n; i++) {
        ll x = a[i];
        auto p = max(dp.query(0, cx.get_id(x-D)+1),
                     dp.query(cx.get_id(x+D), m));
        pre[i] = p.second;
        dp.update(cx.get_id(x), {p.first+1, i});
    }
    int k,i;
    tie(k,i) = dp.query_all();
    cout << k << "\n";
    vector<int> res; res.push_back(i);
    while (k > 1) {
        i = pre[i]; --k;
        res.push_back(i);
    }
    reverse(res.begin(), res.end());
    for (auto& x: res) {
        cout << x+1 << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
