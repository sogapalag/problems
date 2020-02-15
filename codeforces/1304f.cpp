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
#undef LOCAL
string to_string(string s) { return '"' + s + '"'; }
string to_string(bool x) { return (x ? "T" : "F"); }
string to_string(const char* s) { return to_string((string)s); }
template <typename A, typename B>
string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }
template <typename V>
string to_string(V v) {
    bool f = true; string res = "[";
    for (const auto& x: v) {
        if (!f) res += ", ";
        f = false;
        res += to_string(x); } res += "]";
    return res;
}
void debug() { cerr << endl; }
template <typename H, typename... T>
void debug(H h, T... t) { cerr << " " << to_string(h); debug(t...); }
#ifdef LOCAL
#define dbg(args...) cerr<<"("<<#args<<") =", debug(args)
#else
#define dbg(args...) 2020
#endif

const int N = 55; 
const int M = 2e4+10; 
int a[N][M];
int sum(int x,int y,int u,int v){
    return a[u][v] - a[x][v] - a[u][y] + a[x][y];
}
const int INF = 0x3f3f3f3f;
void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 1; i <= n+1; i++) {
        for (int j = 1; j <= m+1; j++) {
            a[i][j] += a[i-1][j] + a[i][j-1] - a[i-1][j-1];
        }
    }
    int lim = m-k+1;
    vector<int> dp(lim);
    for (int j = 0; j < lim; j++) {
        dp[j] = sum(0, j, 2, j+k);
    }
    for (int i = 2; i <= n; i++) {
        vector<int> s(lim), t(lim);
        for (int j = 0; j < lim; j++) {
            s[j] = dp[j] - sum(i-1, 0, i, j+k); // fk, +/- .........!!
            t[j] = dp[j] + sum(i-1, 0, i, j);
        }
dbg(dp,s,t);
        SegTree<int> dpz (dp, -INF, [](int u, int v){ return max(u,v); });
        SegTree<int> dps (s, -INF, [](int u, int v){ return max(u,v); });
        SegTree<int> dpt (t, -INF, [](int u, int v){ return max(u,v); });
        for (int j = 0; j < lim; j++) {
            int tmp = sum(i-1, j, i+1, j+k);
dbg(tmp);
            int& x = dp[j];
            x = 0;
            if (j-k >= 0) {
                x = max(x, dpz.query(0, j-k+1) + tmp);
            }
dbg(x);
            if (j+k < lim) {
                x = max(x, dpz.query(j+k, lim) + tmp);
            }
dbg(x);
            x = max(x, dps.query(max(0, j-k+1), j) + tmp + sum(i-1, 0, i, j));
dbg(x);
            x = max(x, dpt.query(j, min(j+k, lim)) + tmp - sum(i-1, 0, i, j+k));
dbg(x);
        }
dbg(dp);
    }
    int res = *max_element(dp.begin(), dp.end());
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
