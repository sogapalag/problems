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
bool is_build_rev = false;
mint inv[FFTN];
void build_inv(){
    inv[1] = 1;
    for (int i = 2; i < FFTN; i++) {
        inv[i] = (-MOD/i) * inv[MOD%i];
    }
};
bool is_build_inv = false;

template <typename T=mint>
struct Poly : vector<T> {
    using vector<T>::vector;
    Poly() {}
    Poly(initializer_list<T> list) : vector<T>(list) {}

};
template <typename T=mint>
inline Poly<T>& ntt(Poly<T>& a, bool is_inv=false) {
    if (!is_build_rev) { is_build_rev = true; build_rev(); }
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
Poly<T>& trim(Poly<T>& a) {
    while (!a.empty() && a.back() == 0) {
        a.pop_back();
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
Poly<T>& operator+=(Poly<T>& a, const Poly<T>& _p) {
    int n = _p.size();
    if (a.size() < n) {
        a.resize(n);
    }
    for (int i = 0; i < n; i++) {
        a[i] += _p[i];
    }
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
Poly<T> inverse(const Poly<T>& a, int n=0) {
    assert(!a.empty());
    if (!n) n = a.size();
    Poly<T> res = {1/a[0]};
    int k = 1; // res size
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
Poly<T>& operator/=(Poly<T>& a, const Poly<T>& _p) {
    int n = a.size(), m = _p.size();
    if (n < m) { a.clear(); return a; }
    a *= inverse(_p);
    a.resize(n-m+1);
    return a;
}
template <typename T=mint>
Poly<T> sqrt(const Poly<T>& a, int n=0) {
    assert(!a.empty() && a[0] == 1); // TODO need generalize ^{1/2}
    if (!n) n = a.size();
    Poly<T> res = {1};
    int k = 1;  // res size
    T i2 = T(1)/2;
    while (k < n) {
        k <<= 1;
        Poly<T> x(a.begin(), a.begin() + min((int)a.size(), k));
        res.resize(k);
        x *= inverse(res);
        for (int i = k>>1; i < min((int)x.size(), k); i++) {
            res[i] = x[i] * i2;
        }
    }
    res.resize(n);
    return res;
}
template <typename T=mint>
Poly<T>& operator%=(Poly<T>& a, const Poly<T>& _p) {
    int n = a.size(), m = _p.size();
    assert(m > 0);
    if (n >= m) {
        Poly<T> c = (a/_p) * _p;
        a.resize(m-1);
        for (int i = 0; i < m-1; i++) {
            a[i] -= c[i];
        }
    }
    return a;
}

template <typename T=mint> inline Poly<T> operator*(const Poly<T>& _lhs, const Poly<T>& _rhs) { Poly<T> res(_lhs); return res *= _rhs; }
template <typename T=mint> inline Poly<T> operator+(const Poly<T>& _lhs, const Poly<T>& _rhs) { Poly<T> res(_lhs); return res += _rhs; }
template <typename T=mint> inline Poly<T> operator-(const Poly<T>& _lhs, const Poly<T>& _rhs) { Poly<T> res(_lhs); return res -= _rhs; }
template <typename T=mint> inline Poly<T> operator/(const Poly<T>& _lhs, const Poly<T>& _rhs) { Poly<T> res(_lhs); return res /= _rhs; }
template <typename T=mint> inline Poly<T> operator%(const Poly<T>& _lhs, const Poly<T>& _rhs) { Poly<T> res(_lhs); return res %= _rhs; }

template <typename T=mint>
Poly<T> integral(const Poly<T>& a, int n=0) {
    if (!is_build_inv) { is_build_inv = true; build_inv(); }
    if (!n) n = a.size();
    Poly<T> res = a;
    res.resize(n+1);
    for (int i = n; i >= 1; i--) {
        res[i] = res[i-1] * inv[i];
    }
    res[0] = 0;
    return res;
}
template <typename T=mint>
Poly<T> derivative(const Poly<T>& a, int n=0) {
    if (!n) n = a.size();
    Poly<T> res = a;
    res.resize(n);
    for (int i = 0; i < n-1; i++) {
        res[i] = res[i+1] * (i+1);
    }
    res.pop_back();
    return res;
}
template <typename T=mint>
Poly<T> logarithm(const Poly<T>& a, int n=0) {
    if (!n) n = a.size();
    Poly<T> res = interal(derivative(a)/a);
    res.resize(n);
    return res;
}
template <typename T=mint>
Poly<T> exponent(const Poly<T>& a, int n=0) {
    assert(!a.empty() && a[0] = 0);
    if (!n) n = a.size();
    Poly<T> res = {1};
    int k = 1;
    while (k < n) {
        k <<= 1;
        Poly<T> x(a.begin(), a.begin() + min((int)a.size(), k));
        x -= logarithm(res);
        x *= res;
        res.resize(k);
        for (int i = k>>1; i < k; i++) {
            res[i] = x[i];
        }
    }
    res.resize(n);
    return res;
}

using poly=Poly<mint>;

void solve() {
    int n,k;
    cin >> n >> k;
    if (n == 1) {
        cout << "1 ";
        for (int i = 2; i <= k; i++) {
            cout << "0 ";
        }
        return;
    }
    int K = 1; while (K-1 < k) K<<=1;
    K<<=1; // * 2
    //cerr<<K<<endl;
    vector<poly> p(3), f(5);
    for (int i = 0; i < 3; i++) {
        p[i].assign(K, 0);
    }
    for (int i = 0; i < 5; i++) {
        f[i].assign(K, 0);
    }
    // p[i][k]:= dp[n-i][k]
    p[2][0] = 1;
    p[1][0] = p[1][1] = 1;
    p[0][0] = 1, p[0][1] = 3, p[0][2] = 1;
    // a direct dp,advance
    auto Add1 = [&](){
        swap(p[1], p[2]);
        swap(p[0], p[1]);
        for (int i = 0; i <= k; i++) {
            p[0][i] = p[1][i];
            if (i) p[0][i] += p[1][i-1] + p[2][i-1];
        }
        // make sure resize, clear after
        for (int i = k+1; i < K; i++) {
            p[0][i] = 0;
        }
    };
    // e.g. 2n split n*n, (n-1)*(n-1)
    // f[i] rep (n-x)*(n-y) some x+y=i, as below
    auto Mul2 = [&](){
        ntt(p[0]); ntt(p[1]); ntt(p[2]);
        for (int i = 0; i < K; i++) {
            f[0][i] = p[0][i] * p[0][i];
            f[1][i] = p[0][i] * p[1][i];
            f[2][i] = p[1][i] * p[1][i];
            f[3][i] = p[1][i] * p[2][i];
            f[4][i] = p[2][i] * p[2][i];
        }
        for (int i = 0; i < 5; i++) {
            ntt(f[i], true);
        }
        for (int i = 0; i <= k; i++) {
            p[0][i] = f[0][i]; if(i) p[0][i] += f[2][i-1];
            p[1][i] = f[1][i]; if(i) p[1][i] += f[3][i-1];
            p[2][i] = f[2][i]; if(i) p[2][i] += f[4][i-1];
        }
        // make sure clear
        for (int i = k+1; i < K; i++) {
            p[0][i] = 0;
            p[1][i] = 0;
            p[2][i] = 0;
        }
    };
    int x = 2;
    int h = 31 - __builtin_clz(n);
    h--;
    while (x < n) {
        if (n>>h&1) {
            x++;
            Add1();
        }
        if (x < n) {
            x<<=1; h--;
            Mul2();
        }
    }
    assert(x == n);
    for (int i = 1; i <= k; i++) {
        cout << p[0][i] << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
