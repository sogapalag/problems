#include "modular_sim.h"

// http://serbanology.com/show_article.php?art=A%20Bitwise%20Convolution%20Tutorial
// https://csacademy.com/blog/fast-fourier-transform-and-variations-of-it

// SNIPPETS_START fwht
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
    fwht(a); fwht(b);
    for (int i = 0; i < n; i++) {
        a[i] *= b[i];
    }
    return fwht(a, true);
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
// SNIPPETS_END
