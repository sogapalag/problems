#include <bits/stdc++.h>

using namespace std;


// SNIPPETS_START matrix
// n X n, for linear recurrence use
template <typename T>
struct Matrix {
    int n;
    vector<vector<T>> a;

    // Caution: default I
    constexpr Matrix(int _n) : n(_n) {
        a.resize(n);
        for (int i = 0; i < n; i++) {
            a[i].resize(n);
        }
        set_id();
    }
    constexpr Matrix(const Matrix& _m) {
        n = _m.n;
        a = _m.a;
    }
    Matrix& operator=(const Matrix& _m) {
        n = _m.n;
        a = _m.a;
        return *this;
    }
    void set_all(const T& val) {
        for (auto& r: a) {
            for (auto& x: r) {
                x = val;
            }
        }
    }
    void set_id() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = i==j? 1 : 0;
            }
        }
    }
    T trace() {
        T sum = 0;
        for (int i = 0; i < n; i++) {
            sum += a[i][i];
        }
        return sum;
    }
    // sometimes use for v*A
    void transpose() {
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                swap(a[i][j], a[j][i]);
            }
        }
    }
    
    Matrix& operator+=(const Matrix& _m) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] += _m.a[i][j];
            }
        }
        return *this;
    }
    Matrix& operator-=(const Matrix& _m) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] -= _m.a[i][j];
            }
        }
        return *this;
    }
    // if impl as a = tmp*_m.a will WA when A*=A;
    Matrix& operator*=(const Matrix& _m) {
        auto r = a;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                r[i][j] = 0;
                for (int k = 0; k < n; k++) {
                    r[i][j] += a[i][k] * _m.a[k][j];
                }
            }
        }
        a = r;
        return *this;
    }
    // r = A*v
    vector<T> operator*(const vector<T>& v) {
        assert(n == (int)v.size());
        vector<T> res(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                res[i] += a[i][j] * v[j];
            }
        }
        return res;
    }
    Matrix operator+(const Matrix& _m) {
        return Matrix(*this) += _m;
    }
    Matrix operator-(const Matrix& _m) {
        return Matrix(*this) -= _m;
    }
    Matrix operator*(const Matrix& _m) {
        return Matrix(*this) *= _m;
    }
    template <typename U>
    Matrix exp(U e) {
        assert(e >= 0);
        Matrix res(n);
        Matrix b = *this;
        for (; e; e >>= 1) {
            if (e&1) res *= b;
            b *= b;
        }
        return res;
    }
};
// SNIPPETS_END
