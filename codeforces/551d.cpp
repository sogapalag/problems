#include <bits/stdc++.h>

using namespace std;

int MOD[] = {1000000007, 998244353, 998244853};

template <int ITH>
struct modular {
    constexpr modular() : val(0){}
    constexpr modular(const modular& _m) : val(_m.val) {}
    template <typename U> constexpr modular(const U& _r = U()) {
        val = -MOD[ITH] <= _r && _r < MOD[ITH] ? _r: _r % MOD[ITH];
        if (val < 0) { val += MOD[ITH]; } }
    const int operator()() { return val; }
    template <typename U> explicit operator U() const { return static_cast<U>(val); }
    modular& operator+=(const modular& _m) { if ((val += _m.val) >= MOD[ITH]) { val -= MOD[ITH]; } return *this; }
    modular& operator-=(const modular& _m) { if ((val -= _m.val) < 0) { val += MOD[ITH]; } return *this; }
    modular& operator*=(const modular& _m) { val = modular(static_cast<int64_t>(val) * static_cast<int64_t>(_m.val)).val; return *this; }
    modular& operator/=(const modular& _m) {
        int a = _m.val, b = MOD[ITH], u = 0, v = 1;
        while (a != 0) {
            int q = b / a;
            b -= q * a; swap(a, b);
            u -= q * v; swap(u, v); 
        } return *this *= u; }
    modular& operator =(const modular& _m) { val = _m.val; return *this; }
    template <typename U> modular& operator+=(const U& _r) { return *this += modular(_r); }
    template <typename U> modular& operator-=(const U& _r) { return *this -= modular(_r); }
    template <typename U> modular& operator*=(const U& _r) { return *this *= modular(_r); }
    template <typename U> modular& operator/=(const U& _r) { return *this /= modular(_r); } 
    template <typename U> modular& operator =(const U& _r) { val = modular(_r).val; return *this; }
    modular operator-() { return modular(-val); }    
    template <typename U> friend bool operator==(const modular&, const modular&);
    friend std::istream& operator>>(std::istream& os, modular& _m) { os >> _m.val; _m *= 1; return os; }
    friend std::ostream& operator<<(std::ostream& os, const modular& _m) { return os << _m.val; }
    template <typename U>
    modular exp(U e) {
        modular res = 1;
        modular b = val;
        if (e < 0) { b = 1/b; e *= -1; }
        for (; e; e >>= 1) {
            if (e & 1) { res *= b; }
            b *= b;
        } return res; }
private:
    int val;
};
template <int ITH> inline modular<ITH> operator+(const modular<ITH>& _lhs, const modular<ITH>& _rhs) { return modular<ITH>(_lhs) += _rhs; }
template <int ITH, typename U> inline modular<ITH> operator+(const modular<ITH>& _lhs, const U& _rhs) { return modular<ITH>(_lhs) += _rhs; }
template <int ITH, typename U> inline modular<ITH> operator+(const U& _lhs, const modular<ITH>& _rhs) { return modular<ITH>(_lhs) += _rhs; }
template <int ITH> inline modular<ITH> operator-(const modular<ITH>& _lhs, const modular<ITH>& _rhs) { return modular<ITH>(_lhs) -= _rhs; }
template <int ITH, typename U> inline modular<ITH> operator-(const modular<ITH>& _lhs, const U& _rhs) { return modular<ITH>(_lhs) -= _rhs; }
template <int ITH, typename U> inline modular<ITH> operator-(const U& _lhs, const modular<ITH>& _rhs) { return modular<ITH>(_lhs) -= _rhs; }
template <int ITH> inline modular<ITH> operator*(const modular<ITH>& _lhs, const modular<ITH>& _rhs) { return modular<ITH>(_lhs) *= _rhs; }
template <int ITH, typename U> inline modular<ITH> operator*(const modular<ITH>& _lhs, const U& _rhs) { return modular<ITH>(_lhs) *= _rhs; }
template <int ITH, typename U> inline modular<ITH> operator*(const U& _lhs, const modular<ITH>& _rhs) { return modular<ITH>(_lhs) *= _rhs; }
template <int ITH> inline modular<ITH> operator/(const modular<ITH>& _lhs, const modular<ITH>& _rhs) { return modular<ITH>(_lhs) /= _rhs; }
template <int ITH, typename U> inline modular<ITH> operator/(const modular<ITH>& _lhs, const U& _rhs) { return modular<ITH>(_lhs) /= _rhs; }
template <int ITH, typename U> inline modular<ITH> operator/(const U& _lhs, const modular<ITH>& _rhs) { return modular<ITH>(_lhs) /= _rhs; }
template<int ITH> inline bool operator==(const modular<ITH>& _lhs, const modular<ITH>& _rhs) { return _lhs.val == _rhs.val; }
template <int ITH, typename U> inline bool operator==(const modular<ITH>& _lhs, const U& _rhs) { return _lhs == modular<ITH>(_rhs); }
template <int ITH, typename U> inline bool operator==(const U& _lhs, const modular<ITH>& _rhs) { return modular<ITH>(_lhs) == _rhs; }
template <int ITH> inline bool operator!=(const modular<ITH>& _lhs, const modular<ITH>& _rhs) { return !(_lhs == _rhs); }
template <int ITH, typename U> inline bool operator!=(const modular<ITH>& _lhs, const U& _rhs) { return !(_lhs == _rhs); }
template <int ITH, typename U> inline bool operator!=(const U& _lhs, const modular<ITH>& _rhs) { return !(_lhs == _rhs); }
typedef modular<0> mint;
using ll=long long;
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
// note each bit is indep.
// if we wanna 0, then array adj cannot 1,1
//  thus by dp get transi-matrix
void solve() {
    ll n,k; int l;
    cin >> n >> k >> l >> MOD[0];
    int m = k>0?64 - __builtin_clzll(k):0;
    if (m > l) {
        cout << 0; return;
    }
    mint tot = mint(2).exp(n);
    Matrix<mint> a(2);
    a.a[0][0] = a.a[0][1]=1;
    a.a[1][0] = 1; a.a[1][1]=0;
    a = a.exp(n);
    vector<mint> v = {1, 0};
    v = a*v;
    mint noadj = v[0]+v[1];

    mint res = 1;
    for (int i = 0; i < m; i++) {
        if(k>>i&1){
            res *= tot-noadj;
        }else{
            res *= noadj;
        }
    }
    for (int i = m; i < l; i++) {
        res *= noadj;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
