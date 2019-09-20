#include <bits/stdc++.h>

using namespace std;

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
#define dbg(args...) 2019
#endif

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

struct Comb {
    int N;
    vector<mint> fac, ifac, inv;

    Comb(int _n=1) {
        resize(2);
        fac[0] = fac[1] = ifac[0] = ifac[1] = inv[1] = 1;
        N = 1; grow(_n);
    }

    void resize(int _s) {
        fac.resize(_s); ifac.resize(_s); inv.resize(_s);
    }
    bool grow(int _n) {
        if (_n <= N) return false;
        swap(_n, N); resize(N+1);
        for (int i = _n+1; i <= N; i++) {
            fac[i] = fac[i-1] * i;
            inv[i] = (-MOD/i) * inv[MOD%i];
            ifac[i] = ifac[i-1] * inv[i];
        }
        return true;
    }
    // perm
    mint a(int n, int k) {
        if (n < k || k < 0) return 0;
        if (n > N) grow(n);
        return fac[n] * ifac[n-k];
    }
    // choose
    mint c(int n, int k) {
        if (n < k || k < 0) return 0;
        if (n > N) grow(n);
        return fac[n] * ifac[n-k] * ifac[k];
    }
    // sum x = s, x > 0
    mint p(int s, int k) {
        return c(s-1, k-1);
    }
    // sum x = s, x >= 0
    mint z(int s, int k) {
        return p(s+k, k);
    }
    // \E Y-X >= m
    mint hit(int n, int k, int m=1) {
        if (m <= k-n) return c(n+k, n);
        return c(n+k, k-m);
    }
    // catalan trapezoids C_m(n, k)
    // \A Y-X < m,  =c(n+k,n) - hit
    mint cat(int n, int k, int m=1) {
        if (m > k) return c(n+k, n);
        if (m <= k-n) return 0;
        return c(n+k,n) - c(n+k, k-m);
    }
}c(300000);

struct Graph {
    int n, m;
    vector<vector<int>> g;
    bool is_digraph;
    Graph(int _n) : n(_n), m(0) {
        assert(n >= 1);
        g.resize(n);
        set_di(true); // TRUE!
    }
    Graph(int _n, int _m, bool _di=false) : n(_n), m(0) {
        assert(n >= 1);
        assert(1ll*n*(n-1)/2 >= m);
        g.resize(n);
        set_di(_di);
        input(_m);
    }
    inline void add(int u, int v) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        assert(u != v);
        g[u].emplace_back(v);
        pa[v] = u;
        if (!is_digraph)
            g[v].emplace_back(u);
        m++;
    }
    void input(int _m) {
        int u, v;
        for (int i = 0; i < _m; i++) {
            cin >> u >> v;
            u--;v--; // to 0-based
            add(u, v);
        }
    }
    void set_di(bool _di) {
        is_digraph = _di;
        trk = vector<bool>(n, false);
        pa = vector<int>(n, -1);
        sz = vector<int>(n, 0);
        ans = vector<mint>(n, 0);
    }
    vector<bool> trk;
    vector<int> pa;
    vector<int> sz;
    vector<mint> ans;
    void dfs(int u) {
        trk[u] = true;
        ans[u] = 1;
        for (int v: g[u]) {
            if (trk[v]) continue;
            dfs(v);
            ans[u] *= c.ifac[sz[v]]; // different subtree multinorm 
            ans[u] *= ans[v];
            sz[u] += sz[v];
        }
        ans[u] *= c.fac[sz[u]];
        sz[u] += 1;
    }

    void clear_comp(vector<int>& comp) {
        for (int u: comp) {
            trk[u] = false;
            pa[u] = -1;
            sz[u] = 0;
            g[u].clear();
        }
    }

    mint full_dfs(vector<int>& comp){
        mint res = c.fac[comp.size()];
        for (int u: comp) if(pa[u]==-1) {
            dfs(u);
            dbg(sz[u],(int)ans[u]);
            res *= c.ifac[sz[u]]; // comp's sub_comp, multinorm again.
            res *= ans[u];
        }
        return res;
    }
};

// impl so heavy, need to be careful
void solve() {
    int n; cin >> n; int N = n<<1;
    vector<vector<int>> g(N);
    for (int _ = 0; _ < N; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;y+=n;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    for (int i = 0; i < N; i++) {
        sort(g[i].begin(), g[i].end());
    }

    int cycnt = 0, high = -1, low = -1;
    vector<bool> trk(N, false);
    vector<int> pa(N, -1);
    vector<bool> in_c(N, false);
    vector<int> comp;
    vector<int> cycle;
    // find cycle
    function<bool(int,int)> dfs = [&](int u, int p){
        trk[u] = true;
        comp.emplace_back(u);
        for (int v: g[u])if(v!=p){
            if (trk[v]) {
                cycnt++;  high = u;  low = v;
                if (cycnt > 2) return false;
            } else {
                pa[v] = u;
                if (!dfs(v, u)) return false;
            }
        }
        return true;
    };
    // from cycle as start, assign out
    vector<bool> trk_asn(N, false);
    vector<int> assign(N,-1);
    function<void(int)> asn = [&](int u){
        trk_asn[u] = true;
        for (int v: g[u])if(!in_c[v] && !trk_asn[v]){
            assign[v] = u;
            asn(v);
        }
    };

    Graph digraph(N); // dependency graph. directed

    // put adj-smaller than assign to digraph
    auto make_before = [&](int u){
        for (int v: g[u]) {
            if (v >= assign[u]) break;
            digraph.add(u, v);
        }
    };
    mint res = c.fac[N]; // multinorm

    dbg(g);
    for (int i = 0; i < N; i++) {
        if (trk[i]) continue;
        comp.clear(); cycle.clear();
        cycnt = 0, high = -1, low = -1;
        if (!dfs(i, -1) || cycnt < 2) {
            dbg(pa); dbg(cycnt);
            cout << 0; return;
        }
        assert(cycnt == 2 && high != -1 && low != -1);
        {// mark cycle
            int x = low;
            while (x != high) {
                cycle.emplace_back(x);
                in_c[x] = true;
                x = pa[x];
            }cycle.emplace_back(x); in_c[x] = true;
        }
        dbg(high, low);
        dbg(comp, cycle);
        {// assgin out
            for (int u: cycle) asn(u);
        }
        mint sub = 0;
        {// +1
            int csz = cycle.size();
            for (int i = 0; i < csz; i++) {
                assign[cycle[i]] = cycle[(i+1)%csz];
            }
            dbg(assign);
            for (int u: comp){
                make_before(u);
            }
            dbg(digraph.g);
            sub += digraph.full_dfs(comp);
            dbg((int)sub);
            digraph.clear_comp(comp);
        }
        {// -1
            int csz = cycle.size();
            for (int i = 0; i < csz; i++) {
                assign[cycle[i]] = cycle[(i+csz-1)%csz];
            }
            dbg(assign);
            for (int u: comp){
                make_before(u);
            }
            dbg(digraph.g);
            sub += digraph.full_dfs(comp);
            dbg((int)sub);
        }
        res *= c.ifac[comp.size()];
        res *= sub;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
