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

const int N = 4096; 
const int K = 80; 
mint dp[N][K], one[N][K];
mint dn[N][K], up[N][K];

int k;
struct Tree {
    int n;
    vector<vector<int>> g;
    vector<int> tour;
    vector<int> pa;

    Tree(int _n) : n(_n), g(n), pa(n, -1) {
        input();
    }
    void input() {
        for (int _ = 1; _ < n; _++) {
            int x,y;
            cin >> x >> y;
            x--;y--;
            g[x].push_back(y);
            g[y].push_back(x);
        }
    }
    void _dfs(int u,int p){
        tour.push_back(u);
        for (int v:g[u])if(v!=p){
            pa[v] = u;
            _dfs(v,u);
        }
    }
    vector<mint> solve() {
        _dfs(0,-1);
        memset(dp, 0, sizeof dp); // [u][i] : u ->..->u in i steps, without constraint, i.e. can ret many
        memset(one, 0, sizeof one); // [u][i] : u->..->u in i steps. with one time, i.e. #u <=2
        memset(dn, 0, sizeof dn); // [u][i] : u->..->u in i steps. within subtree of u. #u>=0
        memset(up, 0, sizeof up); // [u][i] : u->..->u in i steps. within uptree of u. #u=2
        // dfs, bottom up
        for (int _ = n-1; _ >= 0; _--) {
            int u = tour[_];
            for (int v: g[u])if(v!=pa[u]){
                for (int i = 0; i < k; i+=2) {
                    one[u][i+2] += dn[v][i];
                }
            }
            one[u][0] = dn[u][0] = 1;
            for (int i = 0; i <= k; i+=2) {
                for (int j = 0; j < i; j+=2) {
                    dn[u][i] += dn[u][j] * one[u][i-j];
                }
            }
        }
        // dfs, up-bottom
        for (int u: tour) {
            for (int i = 2; i <= k; i+=2) {
                one[u][i] += up[u][i];
            }
            dp[u][0] = 1;
            for (int i = 0; i <= k; i+=2) {
                for (int j = 0; j < i; j+=2) {
                    dp[u][i] += dp[u][j] * one[u][i-j];
dbg(u, i, j, dp[u][j], one[u][i-j]);
                }
            }
            for (int v: g[u])if(v!=pa[u]){
                // remove u-v subs, force u go other sub or go u-p
                for (int i = 2; i <= k; i+=2) {
                    one[u][i] -= dn[v][i-2];
                }
                up[v][2] = 1;// start from 2, 0 included by dn.
                // below relation is not above convos just cancat.
                // but still bijection corresponding.
                // v,u0...u1...u.u,v  <->  u0...u1 +  v u1...u.u v
                for (int i = 2; i <= k; i+=2) {
                    for (int j = 0; j < i; j+=2) {
                        up[v][i] += up[v][j] * one[u][i-j];
dbg(i,i-j-2,up[v][i], one[u][i-j-2]);
                    }
dbg(v,i,up[v][i]);
                }
                // backup
                for (int i = 2; i <= k; i+=2) {
                    one[u][i] += dn[v][i-2];
                }
            }
        }
        vector<mint> f(k+1);
        for (int u = 0; u < n; u++) {
            for (int i = 0; i <= k; i+=2) {
                f[i] += dp[u][i];
            }
        }
dbg(f);
        return f;
    }
};
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
}c(K);
// note this problem cycle can repeat edge and vertex. don't overcomplicate
// so in projection to T1/T2. it's a walk u..->u. and the two walks comb decide unique cycle.
// so res = sum_{x,y,i}(k,i) dp[x][i]*dp[y][k-i]
//        = sum_i (k,i)f[i] * g[k-i]
void solve() {
    int n1,n2;
    cin >> n1 >> n2 >> k;
    if (k&1){
        cout << 0; return;
    }
    Tree t1(n1), t2(n2);
    auto f = t1.solve();
    auto g = t2.solve();
    mint res = 0;
    for (int i = 0; i <= k; i+=2) {
        res += f[i] * g[k-i] * c.c(k,i);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
