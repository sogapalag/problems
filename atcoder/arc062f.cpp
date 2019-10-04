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
}c(200);

int K;
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

    Graph(int _n) : n(_n), m(0) {
        assert(n >= 1);
        g.resize(n);
        set_di(false);
    }
    Graph(int _n, int _m, bool _di=false) : n(_n) {
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
        int u, v;
        for (int i = 0; i < _m; i++) {
            cin >> u >> v;
            u--; v--; // input 1-based
            add(u, v);
        }
    }
    vector<int> pos;

    int tim;
    vector<int> low;
    vector<int> bg;
    vector<int> pa;
    vector<int> pth;
    vector<int> eth;
    vector<bool> trk;
    mint res;
    void dfs(int u, int p=-1) {
        low[u] = bg[u] = tim++;
        pth.emplace_back(u);
        for (; pos[u] < (int)g[u].size(); pos[u]++) {
            int i = g[u][pos[u]];
            if (p == i) continue; // for un-di, not use same edge. note, can multi-edge
            int v = e[i].u ^ e[i].v ^ u;
            if (bg[v]) {
                low[u] = min(low[u], bg[v]);
            } else {
                dfs(v, i);
                low[u] = min(low[u], low[v]);
                //if (bg[u] < low[v]) {
                //    // bridge found
                //    res *= K;
                //   // pth.pop_back();
                //    eth.pop_back();
                //dbg(pth, eth);
                if (bg[u]<=low[v]) {
                    // compo
                    int sim_cnt = 0;
                    int x=u;
                    // pa maybe over-writen
                    //while (x != v) {
                    //    //assert(low[x] == bg[u]);
                    //    sim_cnt++;
                    //    x = pa[x];
                    //}
                dbg(pth, eth);
                    //do {
                    //    x = pth.back();
                    //    assert(low[x] == bg[u]);
                    //    trk[x] = true;
                    //    pth.pop_back();
                    //    sim_cnt++;// compo_cnt++;
                    //}while(x!=v);
                    fill(trk.begin(), trk.end(), 0);
                    //while (!pth.empty() && low[x=pth.back()] == bg[u]) {
                    //    sim_cnt++;
                    //    trk[x] = true;
                    //    if (x == u) break;
                    //    pth.pop_back();
                    //}
                    do {
                        x = pth.back();
                        trk[x] = true;
                        pth.pop_back();
                    }while(x!=v);
                    trk[u] = true;
                    int compo_cnt = 0;
                    for (int x = 0; x < n; x++) {
                        if (trk[x]){
                            sim_cnt++;
                            for (int j: g[x]) {
                                int y = e[j].u^e[j].v^x;
                                if (trk[y]) compo_cnt++;
                            }
                        }
                    }
                    compo_cnt >>= 1;
                    //do {
                    //    x = eth.back();
                    //    if (x != i) trk[e[x].u] = 1, trk[e[x].v]=1;
                    //    else trk[v] = 1;
                    //    compo_cnt++;
                    //    eth.pop_back();
                    //}while(x != i);
                    //while (eth.back() != i) {
                    //    compo_cnt++;
                    //    eth.pop_back();
                    //}
                dbg(pth, eth);
                dbg(u, v);
                dbg(sim_cnt, compo_cnt);
                    if (compo_cnt < sim_cnt) res*=K;
                    //assert(compo_cnt >= sim_cnt);
                    else if (compo_cnt > sim_cnt) {
                        res *= c.z(compo_cnt, K);
                    } else {
                        mint tmp = 0;
                        for (int j = 1; j <= sim_cnt; j++) {
                            tmp += mint(K).exp(__gcd(j, sim_cnt));
                        }
                        tmp /= sim_cnt;
                        res *= tmp;
                    }
                }
            }
        }
    }
    void dfs_all();
};
void Graph::dfs_all() {
    tim = 1;
    low.assign(n, 0);
    bg.assign(n, 0);
    pa.assign(n, -1);
    trk.assign(n, 0);
    res = 1;
    for (int i = 0; i < n; i++) {
        if (!bg[i]) dfs(i);
    }
}

// edge type : bridge, *K
//             simple cycle, polya
//             else, z(n, K)
// diff type is painful.. if don't be careful.
// do not eth!!  cycle could add repeat.
// bridge compo pop pth careful.
void solve() {
    //mint res = c.z(5, 48) * 48 * 48 *  ((mint(48).exp(5)-48)/5 + 48);
    //assert(res == 569519295);
    int n, m;
    cin >> n >> m >> K;
    Graph g(n,m);
    g.dfs_all();
    cout << g.res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
