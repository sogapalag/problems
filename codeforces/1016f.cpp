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

// similar to 1307f, but forbid adj. so just exclude adj, then recover.
// another method, is find main path. i.e. caterpillar.
//   then discuss. omit.
void solve() {
    int n, q;
    cin >> n >> q;
    vector<vector<pair<int,int>>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x,y,z;
        cin >> x >> y >> z;
        x--;y--;
        g[x].emplace_back(y,z);
        g[y].emplace_back(x,z);
    }
    auto get_dis = [&](int s){
        vector<ll> d(n, -1);
        queue<int> q; q.push(s); d[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto& _: g[u]) {
                int v,w;
                tie(v,w) = _;
                if (d[v] == -1) {
                    d[v] = d[u] + w;
                    q.push(v);
                }
            }
        }
        return d;
    };
    auto d0 = get_dis(0);
    auto d1 = get_dis(n-1);
    ll res = d1[0];

    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](auto& u, auto& v){
        return d0[u]-d1[u] < d0[v]-d1[v];
    });
    const ll NINF = -1ll<<60;
    SegTree<ll> rmx(n, NINF, NINF, [](ll u, ll v){ return max(u,v); });
    vector<int> pos(n, -1);
    vector<bool> trk(n);
    ll msum = NINF;
    for (int i = 0; i < n; i++) {
        int u = id[i]; pos[u] = i;
        trk[u] = true;
        vector<int> del;
        for (auto& _: g[u]) {
            int v,_w;
            tie(v,_w) = _;
            if (trk[v]) {
                rmx.assign(pos[v], NINF);
                del.push_back(v);
            }
        }
        if(i)msum = max(msum, rmx.query(0, i) + d1[u]);
        for (int v: del) {
            rmx.assign(pos[v], d0[v]);
        }
        rmx.assign(i, d0[u]);
    }

    while (q--) {
        int z; cin >> z;
        ll ans = min(res, msum + z);
        cout << ans << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
