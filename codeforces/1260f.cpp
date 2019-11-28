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

#define LOCAL
string to_string(string s) { return '"' + s + '"'; }
string to_string(bool x) { return (x ? "T" : "F"); }
string to_string(mint x) { return to_string(int(x)); }
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

template <typename T, typename U>
struct Seglazy {
    static const int H = 20;
    static const int SZ = 1<<H;
    int sz_v;
    const T ID;  // identity
    const U UN;  // not info
    vector<T> v; // tree
    vector<U> d; // lazy
    
    Seglazy() : sz_v(SZ<<1), ID(0), UN(0), v(sz_v, 0), d(sz_v, 0) {
        //v.resize(sz_v);
        //d.resize(sz_v);
    }
    inline int len(int p) {
        return 1 << (H + __builtin_clz(p) - 31);
    }
    void build(int p=1, int l=0, int r=SZ) {
        if (l + 1 == r) {
            //set leaf
            return;
        }
        assert(l != r);
        int m = (l+r)>>1, pl = p<<1, pr = p<<1|1;
        build(pl, l, m);
        build(pr, m, r);
        v[p] = v[pl] + v[pr];
    }
    inline void apply(int p) {// do!! use info, may need length, pass l, r in
        v[p] += d[p] * len(p);
    }
    inline void store(int p, const U& val) {// do!! store info, careful!! info chain
        d[p] += val;
    }
    inline void push(int p) {
        apply(p);
        if (p <= SZ) {
            store(p<<1, d[p]);
            store(p<<1|1, d[p]);
        }
        d[p] = UN;
    }
    void update(int _l, int _r, const U& val, int p=1, int l=0, int r=SZ) {
        if (d[p] != UN) push(p);
        if (_r <= l || r <= _l) return;
        if (_l <= l && r <= _r) { // update by info
            store(p, val);
            push(p);
            return;
        }
        int m = (l+r)>>1, pl = p<<1, pr = p<<1|1;
        update(_l, _r, val, pl, l, m);
        update(_l, _r, val, pr, m, r);
        v[p] = v[pl] + v[pr];
    }
    T query(int _l, int _r, int p=1, int l=0, int r=SZ) {
        if (d[p] != UN) push(p);
        if (_r <= l || r <= _l) { return ID; }
        if (_l <= l && r <= _r) { return v[p]; }
        int m = (l+r)>>1, pl = p<<1, pr = p<<1|1;
        return query(_l, _r, pl, l, m) + query(_l, _r, pr, m, r);
    }    
};

typedef Seglazy<mint, mint> Seg;

const int N = 100005; 
vector<int> es[N];
mint w[N];

struct HLD {
    int n;
    vector<vector<int>> g;
    vector<int> sz, pa, depth, sta, fin, heavy, top, tour;
    int tim;
    Seg above, below;
    HLD(int _n) : n(_n)
        , g(n)
        , sz(n, 1)
        , pa(n, -1)
        , depth(n)
        , sta(n)
        , fin(n)
        , heavy(n, -1)
        , top(n)
        {
        tour.reserve(n);
        input(); 
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

    void dfs(int u) {
        if (pa[u] != -1) g[u].erase(find(g[u].begin(), g[u].end(), pa[u]));
        for (int& v: g[u]) {
            pa[v] = u;
            depth[v] = depth[u] + 1;
            dfs(v);
            sz[u] += sz[v];
            // heavy skew left, thus chain consective on sta
            if (sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
        }
    }
    // sta*tour = I
    void hld(int u) {
        sta[u] = tim++;
        tour.emplace_back(u);
        for (int v: g[u]) {
            top[v] = (v == g[u][0] ? heavy[u] = v, top[u] : v); // #h=1
            //top[v] = (sz[v] >= (sz[u]+1)/2 ? heavy[u] = v, top[u] : v); // #h<=1
            hld(v);
        }
        fin[u] = tim;
    }
    void build(int root = 0) {
        dfs(root);
        tim = 0; top[root] = root; hld(root);
    }
    inline void across_light(int& v) {
        v = pa[top[v]];
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            sta[u] < sta[v] ? across_light(v) : across_light(u);
        }
        return sta[u] < sta[v] ? u : v;
    }

    using F = function<void(int,int)>; // range operation tim(0)-based [l..r)
    // [u..v]
    void for_v_path(int u, int v, F f) {
        while (true) {
            if (sta[u] > sta[v]) swap(u, v);
            f(max(sta[top[v]], sta[u]), sta[v]+1);
            if (top[u] == top[v]) return;
            across_light(v);
        }
    }
    void for_v_sub(int u, F f, bool exclude = 0) {
        f(sta[u] + exclude, fin[u]);
    }

    mint res;
    void solve() {
        res = 0; mint crt = 0;
        for (int i = 1; i < N; i++) {
            sort(es[i].begin(), es[i].end());
            for (int u: es[i]) {
                mint prob = u>0 ? 1 : -1;
                u = abs(u) - 1;
                prob *= w[u];
                int last = n;
                // below include u, above not
                // u below x <=> x on path [0..u]
                // else x are above
                for_v_path(0, u, [&](int l, int r){
                        crt += prob * below.query(r, last);
                        above.update(r, last, prob);
                        crt += prob * above.query(l, r);
                        below.update(l, r, prob);
                        last = l;
                        });
            }
            res += crt;
//if(i<20)dbg(i, crt, res);
        }
    }
};

// by color-order event, calc contribution on edge
// i.e. split each [l..r), divide 1 to (r-l)'s prob=w[i]. as long as +prob, it contributes.
// crt: current color's prob-sum of above*below
void solve() {
    int n; cin >> n;
    mint tot = 1;
    for (int i = 0; i < n; i++) {
        int l,r;
        cin >> l >> r;
        r++;
        es[l].emplace_back((i+1));
        es[r].emplace_back(-(i+1));
        w[i] = mint(1)/(r-l);
        tot *= r-l;
    }
    HLD hld(n);
    hld.build();
    hld.solve();
    cout << hld.res * tot;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
