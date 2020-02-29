#include <bits/stdc++.h>

using namespace std;
using ll=long long;
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

struct Tree {
    int n;
    vector<vector<pair<int,int>>> g;
    vector<int> sz, pa, sta, fin, tour;
    vector<mint> depth;
    int tim;
    Tree(int _n) : n(_n)
        , g(n)
        , sz(n)
        , pa(n, -1)
        , sta(n)
        , fin(n)
        , depth(n)
        {
        tour.reserve(n);
        input(); 
        tim = 0; basic_dfs(0);
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

    inline void add(int u, int v, int w) {
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    void input() {
        for (int _ = 1; _ < n; _++) {
            int x,y,z;
            cin >> x >> y >> z;
            --x; --y; // to 0-based
            add(x,y,z);
        }
    }
    void basic_dfs(int u) {
        //if (pa[u] != -1) g[u].erase(find(g[u].begin(), g[u].end(), pa[u]));
        sta[u] = tim++;
        tour.emplace_back(u);
        for (auto& _: g[u]) {
            int v,w;
            tie(v,w) = _;
            if (v == pa[u]) continue;
            pa[v] = u;
            depth[v] = depth[u] + w;
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
    mint dist(int u, int v) {
        return depth[u] + depth[v] - 2*depth[lca(u,v)];
    }
    int goup(int u, int step) {
        for (int j = L; j >= 0; j--) {
            if (step>>j&1) u = pa_up[j][u];
        }
        return u;
    }

    // simply apply (x + dx)^2 = x^2 + 2 x dx + dx^2
    //  need careful impl
    void solve() {
        vector<mint> s(n), s2(n);
        for (int _ = n-1; _ >= 0; _--) {
            int u = tour[_];
            for (auto& _: g[u]) {
                int v,w;
                tie(v,w) = _;
                if (v == pa[u]) continue;
                s[u] += s[v] + w * 1ll * sz[v];
                s2[u] += s2[v] + w * 2ll * s[v] + mint(w) * w * sz[v];
            }
        }
        vector<mint> sup(n), s2up(n);
        for (int u:tour){
            for (auto& _: g[u]) {
                int v,w;
                tie(v,w) = _;
                if (v == pa[u]) continue;
                mint ds = sup[u] + (s[u] - s[v] - w*1ll*sz[v]);
                sup[v] += ds + w*1ll*(n-sz[v]);
                s2up[v] += s2up[u] + (s2[u] - s2[v] - w*2ll*s[v] - mint(w)*w*sz[v])
                    + ds*2*w + mint(w)*w*(n-sz[v]);
            }
        }
        // u in sub(v) or not, we calc sub or up, easier
        auto query = [&](int u, int v){
            mint du = s2[u] + s2up[u];
            mint d = dist(u,v);
            if (is_ancestor(v, u)) {
                return du - 2*(s2up[v] + sup[v]*2*d + d*d*(n-sz[v]));
            } else {
                return 2*(s2[v] + s[v]*2*d + d*d*sz[v]) - du;
            }
        };
        int q; cin >> q;
        while (q--) {
            int x,y;
            cin >> x >> y;
            x--;y--;
            cout << query(x,y) << "\n";
        }
    }
};

void solve() {
    int n; cin >> n;
    Tree tr(n); tr.solve();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
