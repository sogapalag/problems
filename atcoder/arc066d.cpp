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

using ll=long long;

mint calc(ll n) {
    map<pair<ll,ll>, mint> dp;
    function<mint(ll,ll)> dfs = [&](ll u, ll v)->mint{
        if (v < 0) return 0;
        if (v == 0) return 1;
        if (dp.count({u,v})) return dp[{u,v}];
        mint res = 0;
        // a,b end, 
        res += dfs(u>>1, v>>1); //0,0
        res += dfs((u-1)>>1, (v-1)>>1); // ^:=1
        if (v>=2) res += dfs(u>>1, (v-2)>>1); // 1,1
        return dp[{u,v}] = res;
    };
    return dfs(n, n);
}

// https://te-sh.github.io/procon2/atc/arc/066/d.html
// dp[.][j] till now, n-v = 0, = 1, >=2.
// then consider a,b, (0,0);
//                    ^:=1;
//                    (1,1).
mint calc2(ll n) {
    mint dp[2][3] = {};
    dp[0][0] = 1;
    int crt = 0;
    for (int i = 60; i >= 0; i--) {
        int nxt = crt ^ 1;
        dp[nxt][0] = dp[nxt][1] = dp[nxt][2] = 0;
        if (n & (1ll<<i)) {
            dp[nxt][1] += dp[crt][0]; dp[nxt][0] += dp[crt][0]; // X
            dp[nxt][2] += dp[crt][1]; dp[nxt][2] += dp[crt][1]; dp[nxt][1] += dp[crt][1];
            dp[nxt][2] += dp[crt][2]; dp[nxt][2] += dp[crt][2]; dp[nxt][2] += dp[crt][2];
        } else {
            dp[nxt][0] += dp[crt][0]; // X                      // X
            dp[nxt][2] += dp[crt][1]; dp[nxt][1] += dp[crt][1]; dp[nxt][0] += dp[crt][1];
            dp[nxt][2] += dp[crt][2]; dp[nxt][2] += dp[crt][2]; dp[nxt][2] += dp[crt][2];
        }
        crt ^= 1;
    }
    mint res = dp[crt][0] + dp[crt][1] + dp[crt][2];
    return res;
}

// http://oeis.org/A007729
// n&1 : k,  when a,b (0,0) or ^:=1. // v <= n
//       k-1, when a,b  (1,1)
// else: k, when a,b (0,0)
//       k-1. when a,b ^:=1 or (1,1)
mint calc3(ll n) {
    map<ll, mint> dp;
    dp[0] = 1; dp[1] = 2;
    function<mint(ll)> f = [&](ll n)->mint{
        if (n < 0) return 0;
        if (dp.count(n)) return dp[n];
        ll k = n >> 1;
        if (n&1) return dp[n] = 2*f(k) + f(k-1);
        else return dp[n] = 2*f(k-1) + f(k);
    };
    return f(n);
}

void solve() {
    ll n; cin >> n;
    mint x = calc(n);
    mint y = calc2(n);
    mint z = calc3(n);
    assert(x==y && y==z);
    cout << z << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
