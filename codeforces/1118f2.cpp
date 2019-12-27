#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353; // 998244853;

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

const int N = 3e5+10; 
mint dp[N][2];
struct Graph {
    struct Edge {
        int u, v;
        int cost;
        Edge(int _u, int _v, int _cost) : u(_u), v(_v), cost(_cost) {}
    };
    int n, m;
    bool is_digraph;
    vector<vector<int>> g;
    vector<Edge> e;
    vector<int> c;
    int C;
    Graph(int _n) : n(_n), m(0), c(n) {
        assert(n >= 1);
        g.resize(n);
        set_di(false);
    }
    Graph(int _n, int _m, bool _di=false) : n(_n), c(n) {
        assert(n >= 1);
        g.resize(n);
        e.reserve(_m);
        m = 0;
        set_di(_di);
        input(_m);
    }
    void set_di(bool _di) {
        pos = vector<int>(n, 0);
        is_digraph = _di;
    }
    inline void add(int u, int v, int cost=1) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        if (is_digraph) {
            //outdeg[u]++; indeg[v]++;
            g[u].emplace_back(m);

        } else {
            //deg[u]++; deg[v]++;
            g[u].emplace_back(m);
            g[v].emplace_back(m);
        }
        e.emplace_back(u, v, cost);
        m++;
    }
    void input(int _m) {
        for (int i = 0; i < n; i++) {
            cin >> c[i];
        }
        int u, v;
        for (int i = 0; i < _m; i++) {
            cin >> u >> v;
            u--; v--; // input 1-based
            dbg("in",u,v);
            add(u, v);
        }
        dbg("?", g);
    }
    vector<int> pos;

    static const int LOG = 20;
    int k;
    vector<int> up[LOG];
    int tim;
    vector<int> bg;
    vector<int> nd;
    void prep(int root);
    void _dfs(int u, int pa) {
        bg[u] = tim++;
        up[0][u] = pa;
        for (int j = 1; j <= k; j++) {
            up[j][u] = up[j-1][up[j-1][u]];
        }
        for (; pos[u] < g[u].size(); pos[u]++) {
            int i = g[u][pos[u]];
            int v = e[i].u ^ e[i].v ^ u;
            // rule
            if (v != pa) _dfs(v, u);
        }
        nd[u] = tim++;
    }
    inline bool _is_ancestor(int u, int v) {
        return bg[u] <= bg[v] && nd[u] >= nd[v];
    }
    inline int lca(int u, int v);

    void dfs(int u, int p) {
        mint tot = 1;
dbg(pos, g[u]);
dbg(u, p);
        for (; pos[u] < g[u].size(); pos[u]++) {
            int i = g[u][pos[u]];
            int v = e[i].u ^ e[i].v ^ u;
            // rule
            if (v != p) {
                dbg(u,v);
                dfs(v, u);
                tot *= (dp[v][0]+dp[v][1]);
            }
        }

        if (c[u]) {
            dp[u][0] = 0; dp[u][1] = tot;
        } else {
            dp[u][0] = tot; dp[u][1] = 0;
            for (int i: g[u]) {
                int v = e[i].u ^ e[i].v ^ u;
                if (v != up[0][u]) {
                    dp[u][1] += tot * dp[v][1] / (dp[v][0] + dp[v][1]);
                }
            }
        }
    }
    void run() {
        fill(pos.begin(), pos.end(), 0);
dbg(g);
dbg(up[0],up[1]);
        dfs(0, -1);
        cout << dp[0][1] << "\n";
    }
};
void Graph::prep(int root=0) {
    k = 32 - __builtin_clz(n);
    for (int j = 0; j <= k; j++) {
        up[j].resize(n);
    }
    bg = vector<int>(n, 0);
    nd = vector<int>(n, 0);
    tim = 1;
    _dfs(root, root);

    // get lca
    vector<int> z(C+1, -1);
    vector<vector<int>> group(C+1);
    for (int i = 0; i < n; i++) {
        int x = c[i];
        if (x) {
            group[x].push_back(i);
            if (z[x]==-1) z[x] = i;
            else {
                z[x] = lca(z[x], i);
            }
        }
    }
    dbg(z, group);
    // render
    for (int x = 1; x <= C; x++) {
        for(int u: group[x]) {
            if (c[u]!=x) {
                cout << 0; exit(0);
            }
            while(u!=z[x]){
                u = up[0][u];
                if (c[u]) {
                    if (c[u]!=x) {
                        dbg(u, c[u],x);
                        cout << 0; exit(0);
                    }else break;
                }else c[u] = x;
            }
            if (c[u]!=x) {
                cout << 0; exit(0);
            }
        }
    }
}
inline int Graph::lca(int u, int v) {
    if (_is_ancestor(u, v)) return u;
    if (_is_ancestor(v, u)) return v;
    for (int j = k; j >= 0; j--) {
        if(!_is_ancestor(up[j][u], v))
            u = up[j][u];
    }
    return up[0][u];
}

// mix up, g/group.. damn
void solve() {
    int n, k;
    cin >> n >> k;
    Graph g(n, n-1); g.C=k;
    g.prep();
    g.run();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
