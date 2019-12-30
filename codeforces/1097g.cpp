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

// [n k]: n into k cycles 
vector<vector<mint>> stir_first(int n) {
    vector<vector<mint>> stir(n+1, vector<mint>(n+1, 0));
    stir[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            stir[i][j] = stir[i-1][j-1] + stir[i-1][j]*(i-1);
        }
    }
    return stir;
}
// {n k}: n into k sets
vector<vector<mint>> stir_second(int n) {
    vector<vector<mint>> stir(n+1, vector<mint>(n+1, 0));
    stir[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            stir[i][j] = stir[i-1][j-1] + stir[i-1][j]*j;
        }
    }
    return stir;
}
// using, x^n = sum_{k:0..=n} {n k} (x)_k
// (x)_n := x*(x-1)...(x-n+1)
vector<mint> fall_table(int x, int n) {
    vector<mint> res(n+1);
    res[0] = 1;
    for (int i = 1; i <= n; i++) {
        res[i] = res[i-1] * (x-i+1);
    }
    return res;
}
vector<mint> rise_table(int x, int n) {
    vector<mint> res(n+1);
    res[0] = 1;
    for (int i = 1; i <= n; i++) {
        res[i] = res[i-1] * (x+i-1);
    }
    return res;
}
vector<mint> power_table(mint x, int n) {
    vector<mint> pw(n+1);
    pw[0] = 1;
    for (int i = 1; i <= n; i++) {
        pw[i] = pw[i-1] * x;
    }
    return pw;
}

const int N = 100005; 
const int K = 211; 
mint dp[N][K];
mint f[K], convo[K];

// https://codeforces.com/blog/entry/64367
// https://www.cnblogs.com/TinyWong/p/10436870.html
//
// first tuple trick, sum {k i}i!. C(|X|=i)  X: a set of edges
// need cnt C(X) how many ways, X subs Cons. which is shape divide to scc. corner (2^s-1), else vertex *=2
// the trick part is to handle case like
//    |    |
//    |   / \ . 
//  that up-compo could (2^? -1)
// for lower compo, dp[u][1]-=1. is fine.
// trick part for up. use something similar mobius, or IEP.
//   that base case and odd case can be handled correctly
void solve() {
    int n,k;
    cin >> n >> k;
    auto stir2 = stir_second(k);
    auto fac = rise_table(1, k);
    vector<vector<int>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }

    vector<int> sz(n,1);
    function<void(int,int)> dfs = [&](int u,int p){
        dp[u][0] = 2;
        for (int v:g[u])if(v!=p){
            dfs(v,u);
            for (int i = 0; i <= min(sz[u],k); i++) {
                for (int j = 0; j <= min(sz[v],k); j++) {
                    if (i+j>k) break;
                    convo[i+j] += dp[u][i] * dp[v][j];
                }
            }
            // eliminate, acoording below, then on sub u
            // base case would calceled with below +.
            // odd 
            for (int j = 0; j <= min(sz[v],k); j++) {
                f[j] -= dp[v][j];
            }
            sz[u] += sz[v];
            for (int i = 0; i <= min(sz[u], k); i++) {
                dp[u][i] = convo[i]; convo[i] = 0;
            }
        }
        // on sub u.
        for (int i = 0; i <= min(sz[u], k); i++) {
            f[i] += dp[u][i];
        }
        // use u-p, but don't consider p's *=2
        for (int i = min(sz[u], k); i > 0; i--) {
            dp[u][i] += dp[u][i-1];
        }
        // all vertex <=u not choose
        dp[u][1] -= 1;
    };
    dfs(0,-1);

    mint res = 0;
    for (int i = 1; i <= min(n-1, k); i++) {
        res += stir2[k][i] * fac[i] * f[i];
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
