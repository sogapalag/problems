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

template <typename T=mint>
struct Boly : vector<T> {
    using vector<T>::vector;
    Boly() {}
    Boly(initializer_list<T> list) : vector<T>(list) {}

};

template <typename T=mint>
inline Boly<T>& fwht(Boly<T>& a, bool is_inv=false) {
    int n = a.size();
    assert((n&(n-1)) == 0);
    if (is_inv) {
        T i_n = T(1)/n;
        for (int i = 0; i < n; i++) {
            a[i] *= i_n;
        }
    }
    for (int m = 1; m < n; m<<=1) {
        int l = m<<1;
        for (int i = 0; i < n; i+=l) {
            for (int j = 0; j < m; j++) {
                T x = a[i+j];
                T y = a[i+j+m];
                a[i+j] = x + y;
                a[i+j+m] = x - y;
            }
        }
    }
    return a;
}

// 0 1
// 1 1
// verified by zeta. check /transform/fast_superset_convolution_join
template <typename T>
inline Boly<T>& and_fwht(Boly<T>& a, bool is_inv=false) {
    int n = a.size();
    assert((n&(n-1)) == 0);
    for (int m = 1; m < n; m<<=1) {
        int l = m<<1;
        for (int i = 0; i < n; i+=l) {
            for (int j = 0; j < m; j++) {
                T x = a[i+j];
                T y = a[i+j+m];
                if (!is_inv) {
                    a[i+j] = y;
                    a[i+j+m] = x + y;
                } else {
                    a[i+j] = -x + y;
                    a[i+j+m] = x;
                }
            }
        }
    }
    return a;
}

// 1 1
// 1 0
// verified by zeta. check /transform/fast_subset_convolution_union
template <typename T>
inline Boly<T>& or_fwht(Boly<T>& a, bool is_inv=false) {
    int n = a.size();
    assert((n&(n-1)) == 0);
    for (int m = 1; m < n; m<<=1) {
        int l = m<<1;
        for (int i = 0; i < n; i+=l) {
            for (int j = 0; j < m; j++) {
                T x = a[i+j];
                T y = a[i+j+m];
                if (!is_inv) {
                    a[i+j] = x + y;
                    a[i+j+m] = x;
                } else {
                    a[i+j] = y;
                    a[i+j+m] = x - y;
                }
            }
        }
    }
    return a;
}

template <typename T=mint>
Boly<T>& operator*=(Boly<T>& a, const Boly<T>& _b) {
    int n = max(a.size(), _b.size());
    int _n = 1 << (31 - __builtin_clz(n));
    if (_n < n) n = _n<<1;
    auto b = _b;
    a.resize(n); b.resize(n);
    //fwht(a); fwht(b);
    and_fwht(a); and_fwht(b);
    for (int i = 0; i < n; i++) {
        a[i] *= b[i];
    }
    return and_fwht(a, true);
}
// note solution could many, (1,1,...,1) * b = 0, if \sum b = 0
template <typename T=mint>
Boly<T>& operator/=(Boly<T>& a, const Boly<T>& _b) {
    int n = max(a.size(), _b.size());
    int _n = 1 << (31 - __builtin_clz(n));
    if (_n < n) n = _n<<1;
    auto b = _b;
    a.resize(n); b.resize(n);
    fwht(a); fwht(b);
    for (int i = 0; i < n; i++) {
        a[i] /= b[i];
    }
    return fwht(a, true);
}
template <typename T=mint> inline Boly<T> operator*(const Boly<T>& a, const Boly<T>& _b) { Boly<T> res(a); return res *= _b; }
template <typename T=mint> inline Boly<T> operator/(const Boly<T>& a, const Boly<T>& _b) { Boly<T> res(a); return res /= _b; }

using boly=Boly<mint>;

template <typename T>
T pow(T x, int64_t e) {
    T res(1<<20); res[(1<<20)-1] = 1;
    for (; e; e >>= 1) {
        if (e & 1) res *= x;
        x *= x;
    }
    return res;
}

void stupid_solve() {
    int n; cin >> n;
    Boly<mint> b(1<<20);
    b[0] = 1;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        b[x] = 1;
    }
    auto r = pow(b, n); // direct pow, additional_log
    int res = 0;
    for (auto& x: r) {
        if (x != 0) res++;
    }
    cout << res;
}
// a robust way use two MODs in case of MOD=0
// T(A*B) = TA TB
// T(A*B*C) = T(A*B)T(C)= TA TB TC
void fast_solve() {
    int n; cin >> n;
    Boly<mint> b(1<<20);
    b[0] = 1;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        b[x] = 1;
    }
    // b^e = T^-1 (Tb)^_{element}e
    and_fwht(b);
    for (auto& x: b) {
        x = x.exp(n);
    }
    and_fwht(b, true);

    int res = 0;
    for (auto& x: b) {
        if (x!=0)res++;
    }
    cout << res;
}
// O(n 2^n) Yates
#define __loop(f) \
    for (int i = 0, n = 31-__builtin_clz((int)f.size()), MSK = 1<<n; i < n; i++)\
        for (int msk = 0; msk < MSK; msk++)\
            if (msk>>i&1)

template <typename T>
inline void fast_superset_zeta_transform(vector<T>& f) {
    __loop(f) f[msk ^ 1<<i] += f[msk];
}
template <typename T>
inline void fast_superset_mobius_transform(vector<T>& f) {
    __loop(f) f[msk ^ 1<<i] -= f[msk];
}
template <typename T>
inline void fast_superset_convolution_join(vector<T>& f, vector<T>& g) {
    fast_superset_zeta_transform(f);
    fast_superset_zeta_transform(g);
    int MSK = f.size();
    for (int i = 0; i < MSK; i++) {
        f[i] *= g[i];
    }
    fast_superset_mobius_transform(f);
}

void fast_solve_zeta() {
    int n; cin >> n;
    vector<mint> b(1<<20);
    b[0] = 1;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        b[x] = 1;
    }
    // b^e = T^-1 (Tb)^_{element}e
    fast_superset_zeta_transform(b);
    for (auto& x: b) {
        x = x.exp(n);
    }
    fast_superset_mobius_transform(b);

    int res = 0;
    for (auto& x: b) {
        if (x!=0)res++;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    fast_solve_zeta();
    cout << endl;
}
