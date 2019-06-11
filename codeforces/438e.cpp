#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;

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


mint GEN = 3; // generator 

const int FFTH = 18; // 21;
const int FFTN = 1<<FFTH; 
int REV[FFTH][FFTN];
void build_rev() {
    for (int h = 0; h < FFTH; h++) {
        int n = 1 << (h+1);
        REV[h][0] = 0;
        for (int i = 1; i < n; i++) {
            REV[h][i] = (REV[h][i>>1] >> 1) | ((i&1) << h);
        }
    }
}
bool is_build = false;

template <typename T=mint>
struct Poly : vector<T> {
    using vector<T>::vector;
    Poly() {}
    Poly(initializer_list<T> list) : vector<T>(list) {}

};
template <typename T=mint>
inline Poly<T>& ntt(Poly<T>& a, bool is_inv=false) {
    if (!is_build) { is_build = true; build_rev(); }
    int n = a.size();
    assert(n>1 && (n&(n-1)) == 0);
    int h = 31 - __builtin_clz(n) - 1;
    if (is_inv) {
        T i_n = T(1)/n;
        for (int i = 0; i < n; i++) {
            a[i] *= i_n;
        }
        reverse(a.begin()+1, a.end());
    }
    for (int i = 0; i < n; i++) {
        int j = REV[h][i];
        if (i < j) swap(a[i], a[j]);
    }
    for (int m = 1; m < n; m<<=1) {
        int l = m<<1;
        assert((MOD-1) % l == 0);
        T _w = GEN.exp((MOD-1)/l);
        for (int i = 0; i < n; i+=l) {
            T w = 1;
            for (int j = 0; j < m; j++) {
                T x = a[i+j];
                T y = w * a[i+j+m];
                a[i+j] = x + y;
                a[i+j+m] = x - y;
                w *= _w;
            }
        }
    }
    return a;
}
template <typename T=mint>
Poly<T>& operator*=(Poly<T>& a, const Poly<T>& _p) {
    if (a.empty() || _p.empty()) { a.clear(); return a; }
    int n = a.size() + _p.size() - 1;
    int old = n;
    if (n == 1) {a[0] *= _p[0]; return a; }
    int _n = 1 << (31-__builtin_clz(n));
    if (_n < n) n = _n<<1;
    auto p = _p;
    p.resize(n); ntt(p);
    a.resize(n); ntt(a);
    for (int i = 0; i < n; i++) {
        a[i] *= p[i];
    }
    ntt(a, true); a.resize(old);
    return a;
}
template <typename T=mint>
Poly<T>& operator-=(Poly<T>& a, const Poly<T>& _p) {
    int n = _p.size();
    if (a.size() < n) {
        a.resize(n);
    }
    for (int i = 0; i < n; i++) {
        a[i] -= _p[i];
    }
    return a;
}
template <typename T=mint>
Poly<T> inv(const Poly<T>& a, int n=0) {
    assert(!a.empty());
    if (!n) n = a.size();
    Poly<T> res = {1/a[0]};
    int k = 1;
    while (k < n) {
        k <<= 1;
        Poly<T> a_cut(a.begin(), a.begin() + min((int)a.size(), k));
        Poly<T> x = res * res * a_cut;
        res.resize(k);
        for (int i = k>>1; i < min((int)x.size(), k); i++) {
            res[i] -= x[i];
        }

    }
    res.resize(n);
    return res;
}
template <typename T=mint>
Poly<T> sqrt(const Poly<T>& a) {
    assert(!a.empty());
    int n = a.size();
    Poly<T> res = {1};
    int k = 1;
    T i2 = T(1)/2;
    while (k < n) {
        k <<= 1;
        Poly<T> x(a.begin(), a.begin() + min((int)a.size(), k));
        res.resize(k);
        x *= inv(res);
        for (int i = k>>1; i < min((int)x.size(), k); i++) {
            res[i] = x[i] * i2;
        }
    }
    res.resize(n);
    return res;
}
template <typename T=mint> inline Poly<T> operator*(const Poly<T>& _lhs, const Poly<T>& _rhs) { Poly<T> res(_lhs); return res *= _rhs; }
using poly=Poly<mint>;
void solve() {
    int n, m;
    cin >> n >> m;
    poly c(1 << 17);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        c[x] = 1;
    }
    int sz = 1 << (31-__builtin_clz(m+1));
    if (sz < m+1) sz <<= 1;
    c.resize(sz);
    for (mint& x: c) {
        x *= -4;
    }
    c[0] += 1;
    c = sqrt(c);
    c[0] += 1;
    c = inv(c);
    for (mint& x: c) {
        x *= 2;
    }
    for (int i = 1; i <= m; i++) {
        cout << c[i] << "\n";
    }
  //  poly p = c;
  //  //p = 4*p;
  //  p = 2 / (1+(1-4*p).sqrt());
  //  for (int i = 1; i <= m; i++) {
  //      cout << p.a[i] << "\n";
  //  }
  //  vector<mint> a = {1, 6, 9, 0};
  //  poly p = {1, 6, 9, 0};
  //  poly r = sqrt(p);
  //  //poly r = p.inv(100000);
  //  for (auto& x: r) {
  //      cout << x << ' ';
  //  }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
