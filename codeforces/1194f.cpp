#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007; // 998244353

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
// first sum i p_i =  sum p_{>=i}
// so for 1~i tasks, remain extra time  d = T - sum[i]
// and (1 + 0)^i, that
// p_{>=i}  = C(i, <=d) = C(i, 0)+C(i,1)+..C(i, d) , then * 1/2^i;
// a naive impl, O(n^2) solution.
// but since i +1 inc. and d dec.
// and F = C(i, <=d) = 2 * C(i-1, <=d) - C(i-1, d); by C(n, k) = C(n-1,k)+C(n-1,k-1).
// so optimized
void solve() {
    int n; ll T;
    cin >> n >> T;
    vector<ll> sum(n+1);
    sum[0] = 0;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        sum[i] = sum[i-1] + x;
    }
    int _n = n;
    vector<mint> fac(_n+1);
    vector<mint> ifac(_n+1);
    vector<mint> inv(_n+1);
    auto build = [&](){
        fac[0] = fac[1] = 1;
        ifac[0] = ifac[1] = 1;
        inv[1] = 1;
        for (int i = 2; i <= _n; i++) {
            fac[i] = fac[i-1] * i;
            inv[i] = (-MOD/i) * inv[MOD%i];
            ifac[i] = ifac[i-1] * inv[i];
        }
    };
    build();
    vector<mint> pw(n+1);
    pw[0] = 1;
    mint half = mint(1)/2;
    for (int i = 1; i <= n; i++) {
        pw[i] = pw[i-1] * half;
    }
    auto c = [&](int k, int i){
        if (k < i || i < 0) return mint(0);
        return fac[k] * ifac[i] * ifac[k-i];
    };
  //  auto f = [&](int k, ll d){
  //      if (d < 0) return mint(0);
  //      if (d >= k) return mint(1);
  //      mint tmp = 0;
  //      for (int i = 0; i <= d; i++) {
  //          tmp += c(k, i);
  //      }
  //      return tmp * pw[k];
  //  };
   // map<pair<int,ll>, mint> mp;
   // mint half = mint(1)/2;
   // function<mint(int, ll)> f = [&](int k, ll d){
   //     if (d < 0) return mint(0);
   //     if (d >= k) return mint(1);
   //     if (mp.find({k,d}) != mp.end()) return mp[{k,d}];
   //     return (f(k-1, d) + f(k-1, d-1)) * half;
   // };
    mint res = 0;
    mint F = 1; int r = 0;
    for (int i = 1; i <= n; i++) {
        ll d = T - sum[i];
        if (d < 0) break;
        F = 2*F - c(i-1, r); // key optimization
        while (r < min((ll)i, d)) {
            F += c(i, ++r);
        }
        while (r > d) {
            F -= c(i, r--);
        }
        res += F * pw[i];
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
