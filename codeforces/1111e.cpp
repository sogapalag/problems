#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007; // 998244353; // 998244853; 

template <typename T>
struct modular {
    constexpr modular() : val(0){}
    constexpr modular(const modular<T>& _m) : val(_m.val) {}
    template <typename U> constexpr modular(const U& _r = U()) {
        val = -MOD <= _r && _r < MOD ? _r: _r % MOD;
        if (val < 0) { val += MOD; } }
    const T operator()() { return val; }
    template <typename U> explicit operator U() const { return static_cast<U>(val); }
    modular<T>& operator+=(const modular<T>& _m) { if ((val += _m.val) >= MOD) { val -= MOD; } return *this; }
    modular<T>& operator-=(const modular<T>& _m) { if ((val -= _m.val) < 0) { val += MOD; } return *this; }
    modular<T>& operator*=(const modular<T>& _m) { val = modular<T>(static_cast<int64_t>(val) * static_cast<int64_t>(_m.val)).val; return *this; }
    modular<T>& operator/=(const modular<T>& _m) {
        T a = _m.val, b = MOD, u = 0, v = 1;
        while (a != 0) {
            T q = b / a;
            b -= q * a; swap(a, b);
            u -= q * v; swap(u, v); 
        } return *this *= u; }
    modular<T>& operator =(const modular<T>& _m) { val = _m.val; return *this; }
    template <typename U> modular<T>& operator+=(const U& _r) { return *this += modular<T>(_r); }
    template <typename U> modular<T>& operator-=(const U& _r) { return *this -= modular<T>(_r); }
    template <typename U> modular<T>& operator*=(const U& _r) { return *this *= modular<T>(_r); }
    template <typename U> modular<T>& operator/=(const U& _r) { return *this /= modular<T>(_r); } 
    template <typename U> modular<T>& operator =(const U& _r) { val = modular<T>(_r).val; return *this; }
    modular<T> operator-() { return modular<T>(-val); }    
    template <typename U> friend bool operator==(const modular<U>&, const modular<U>&);
    friend std::istream& operator>>(std::istream& os, modular<T>& _m) { os >> _m.val; _m *= 1; return os; }
    friend std::ostream& operator<<(std::ostream& os, const modular<T>& _m) { return os << _m.val; }
    template <typename U>
    modular<T> exp(U e) {
        modular<T> res = 1;
        modular<T> b = val;
        if (e < 0) { b = 1/b; e *= -1; }
        for (; e; e >>= 1) {
            if (e & 1) { res *= b; }
            b *= b;
        } return res; }
private:
    T val;
};
template <typename T> inline modular<T> operator+(const modular<T>& _lhs, const modular<T>& _rhs) { return modular<T>(_lhs) += _rhs; }
template <typename T, typename U> inline modular<T> operator+(const modular<T>& _lhs, const U& _rhs) { return modular<T>(_lhs) += _rhs; }
template <typename T, typename U> inline modular<T> operator+(const U& _lhs, const modular<T>& _rhs) { return modular<T>(_lhs) += _rhs; }
template <typename T> inline modular<T> operator-(const modular<T>& _lhs, const modular<T>& _rhs) { return modular<T>(_lhs) -= _rhs; }
template <typename T, typename U> inline modular<T> operator-(const modular<T>& _lhs, const U& _rhs) { return modular<T>(_lhs) -= _rhs; }
template <typename T, typename U> inline modular<T> operator-(const U& _lhs, const modular<T>& _rhs) { return modular<T>(_lhs) -= _rhs; }
template <typename T> inline modular<T> operator*(const modular<T>& _lhs, const modular<T>& _rhs) { return modular<T>(_lhs) *= _rhs; }
template <typename T, typename U> inline modular<T> operator*(const modular<T>& _lhs, const U& _rhs) { return modular<T>(_lhs) *= _rhs; }
template <typename T, typename U> inline modular<T> operator*(const U& _lhs, const modular<T>& _rhs) { return modular<T>(_lhs) *= _rhs; }
template <typename T> inline modular<T> operator/(const modular<T>& _lhs, const modular<T>& _rhs) { return modular<T>(_lhs) /= _rhs; }
template <typename T, typename U> inline modular<T> operator/(const modular<T>& _lhs, const U& _rhs) { return modular<T>(_lhs) /= _rhs; }
template <typename T, typename U> inline modular<T> operator/(const U& _lhs, const modular<T>& _rhs) { return modular<T>(_lhs) /= _rhs; }
template <typename T> inline bool operator==(const modular<T>& _lhs, const modular<T>& _rhs) { return _lhs.val == _rhs.val; }
template <typename T, typename U> inline bool operator==(const modular<T>& _lhs, const U& _rhs) { return _lhs == modular<T>(_rhs); }
template <typename T, typename U> inline bool operator==(const U& _lhs, const modular<T>& _rhs) { return modular<T>(_lhs) == _rhs; }
template <typename T> inline bool operator!=(const modular<T>& _lhs, const modular<T>& _rhs) { return !(_lhs == _rhs); }
template <typename T, typename U> inline bool operator!=(const modular<T>& _lhs, const U& _rhs) { return !(_lhs == _rhs); }
template <typename T, typename U> inline bool operator!=(const U& _lhs, const modular<T>& _rhs) { return !(_lhs == _rhs); }
typedef modular<int> mint;

template <typename T=int>
struct Fenwick {
    int n;
    vector<T> v;
    
    Fenwick(int size = 100005) : n(size), v(n+1, 0) {}
    inline void add(int p, T val) {
        for (; p <= n; p += (p&-p)) { v[p] += val; }
    }
    inline T query(int p) {
        T tmp = 0;
        for (; p > 0; p -= (p&-p)) { tmp += v[p]; }
        return tmp;
    }
    inline T query(int l, int r) {
        return query(r) - query(l-1);
    }
};
template <typename T>
struct RASQ {
    int n;
    Fenwick<T> diff;

    RASQ(int _n) : n(_n), diff(n) {}
    // 1-based, [l..r)
    inline void add(int l, int r, T val) {
        diff.add(l, val);
        diff.add(r, -val);
    }
    inline T query(int p) {
        return diff.query(p);
    }
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
struct Tree {
    int n;
    vector<vector<int>> g;
    vector<int> sz, pa, depth, sta, fin, tour;
    int tim;
    RASQ<int> rasq;
    Tree(int _n) : n(_n)
        , g(n)
        , sz(n)
        , pa(n, -1)
        , depth(n)
        , sta(n)
        , fin(n)
        , rasq(n)
        , trk(n)
        {
        tour.reserve(n);
        input(); 
        tim = 1; basic_dfs(0);
        build_lca();
    }
    int L;
    vector<vector<int>> pa_up;
    void build_lca() {
        L = 0; while ((1<<L) < n-1) L++;
        pa_up = vector<vector<int>>(L+1, vector<int>(n));
        pa[0] = 0; // root-self
        for (int u: tour) {
            pa_up[0][u] = pa[u];
            for (int j = 1; j <= L; j++) {
                pa_up[j][u] = pa_up[j-1][ pa_up[j-1][u] ];
            }
        }
    }

    inline void add(int u, int v) {
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    void input() {
        for (int _ = 1; _ < n; _++) {
            int x,y;
            cin >> x >> y;
            --x; --y; // to 0-based
            add(x,y);
        }
    }
    void basic_dfs(int u) {
        if (pa[u] != -1) g[u].erase(find(g[u].begin(), g[u].end(), pa[u]));
        sta[u] = tim++;
        tour.emplace_back(u);
        for (int& v: g[u]) {
            pa[v] = u;
            depth[v] = depth[u] + 1;
            basic_dfs(v);
            sz[u] += sz[v];
        }
        ++sz[u];
        fin[u] = tim;
    }
    inline bool is_ancestor(int u, int v) {
        return sta[u] <= sta[v] && fin[v] <= fin[u];
    }
    inline int lca(int u, int v) {
        if (is_ancestor(u, v)) return u;
        if (is_ancestor(v, u)) return v;
        for (int j = L; j >= 0; j--) {
            if(!is_ancestor(pa_up[j][u], v))
                u = pa_up[j][u];
        }
        return pa_up[0][u];
    }
    int dist(int u, int v) {
        return depth[u] + depth[v] - 2*depth[lca(u,v)];
    }
    int goup(int u, int step) {
        for (int j = L; j >= 0; j--) {
            if (step>>j&1) u = pa_up[j][u];
        }
        return u;
    }

    vector<bool> trk;
    // the key is process by dfs order, the only needed info is how many ances of u.
    //   with reroot, which => path cnt(by BIT) + lca.
    void solve() {
        int k,m,r;
        cin >> k >> m >> r; r--;
        // by dfs order, relax-> depth order
        vector<int> a(k);
        vector<pair<int, int>> da(k);
        for (int i = 0; i < k; i++) {
            cin >> a[i]; --a[i];
            da[i] = {dist(a[i], r), a[i]};
        }
        sort(da.begin(), da.end());
        for (int i = 0; i < k; i++) {
            a[i] = da[i].second;
        }
        //sort(a.begin(), a.end(), [&](auto& u, auto& v){
        //    return dist(u,r) < dist(v,r);
        //});
dbg(a);
        // #trk[0..u]
        auto cnt0 = [&](int u){
            return rasq.query(sta[u]);
        };
        // #trk[r..u)
        auto cntr = [&](int u) {
            return cnt0(u) + cnt0(r) - 2*cnt0(lca(u,r)) + (int)(trk[lca(u,r)]) - 1;
        };
        vector<vector<mint>> dp(2, vector<mint>(m+2));
        dp[0][0] = 1;
        int crt = 0;
        for (int i = 0; i < k; i++) {
            int u = a[i]; trk[u] = true;
            rasq.add(sta[u], fin[u], 1);
            int x = cntr(u);
dbg(u, x);
            int nxt = crt ^ 1;
            fill(dp[nxt].begin(), dp[nxt].end(), 0);
            for (int j = 0; j <= i && j <= m; j++) {
                dp[nxt][j+1] += dp[crt][j];
                if (j>x)dp[nxt][j] += dp[crt][j] * (j - x);
            }
            crt ^= 1;
        }
        mint res = 0;
        for (int j = 1; j <= m; j++) {
            res += dp[crt][j];
        }
        cout << res << "\n";
        // reset
        for (int u: a) rasq.add(sta[u], fin[u], -1), trk[u]=false;
    }
    void process(int q) {
        while(q--)solve();
    }
};

// note group no necessary scc, as long as no ances.
void solve() {
    int n,q; cin >> n >> q;
    Tree tr(n); tr.process(q);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
