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

#define __up_loop(f) \
    for (int n = f.size(), i = 1; i < n; i++)\
        for (int j = i; (j += i) < n;)
#define __dn_loop(f) \
    for (int n = f.size(), i = n-1; i >= 1; i--)\
        for (int j = i; (j += i) < n;)

template <typename T>
inline void zeta(vector<T>& f) {
    __dn_loop(f) f[j] += f[i];
}
template <typename T>
inline void mobius(vector<T>& F) {
    __up_loop(F) F[j] -= F[i];
}
template <typename T>
inline void zeta_p(vector<T>& f) {
    __up_loop(f) f[i] += f[j];
}
template <typename T>
inline void mobius_p(vector<T>& F) {
    __dn_loop(F) F[i] -= F[j];
}
template <typename T>
inline void convolution_gcd(vector<T>& f, vector<T>& g) {
    zeta_p(f);
    zeta_p(g);
    int n = f.size();
    for (int i = 1; i < n; i++) {
        f[i] *= g[i];
    }
    mobius_p(f);
}
const int N = 1e7+7; 


// problem ask #(x,S) s.t. gcd(x, S)= 1, gcd(S)>1
void solve() {
    int n; cin >> n;
    vector<int> cnt(N);
    for (int _ = 0; _ < n; _++) {
        int x;cin >> x;
        cnt[x]++;
    }
    clock_t beg = clock();

    zeta_p(cnt);
    vector<mint> F(N), pw(n+1);
    pw[0]=1;
    for (int i = 1; i <= n; i++) {
        pw[i]=pw[i-1]*2;
    }

    for (int i = 1; i < N; i++) {
        int k = cnt[i];
        F[i] = pw[k]-1;
    }
    // just direct do convo, TLE
    //mobius_p(F); F[1] = 0;  // F[g] = #gcd=g
    //convolution_gcd(a, F);

    // less loops, AC
    //mobius_p(F); F[1] = 0;
    //zeta_p(F);
    //for (int i = 1; i < N; i++) {
    //    F[i] *= cnt[i];
    //}
    //mobius_p(F);

    for (int i = 2; i < N; i++) {
        F[i] *= n - cnt[i];
    }
    // now F[i]:= i|gcd(S), gcd(x,S) <| i
    F[1] = 0;
    // although we use mobius_p, but better think it as -mu[i]*F[i]
    // think some cases, 2,3,4;  2,3,6
    // square is considered by smaller prime. and 6->3, is calceld from 2(6)->3
    mobius_p(F);
    clock_t end = clock();
    //cerr << (double)(end-beg)/CLOCKS_PER_SEC << endl;
    cout << -F[1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
