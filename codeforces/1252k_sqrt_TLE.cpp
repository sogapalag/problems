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

// n X n, for linear recurrence use
template <typename T>
struct Matrix {
    int n;
    vector<vector<T>> a;

    // Caution: default I
    constexpr Matrix(int _n=2) : n(_n) {
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

const int BLOCK_SIZE = 256; 

Matrix<mint> A, B;

struct Block {
    int L, R;
    char s[BLOCK_SIZE];
    bool toggled;
    Matrix<mint> a, dual;

    Block(int _L, int _R) : L(_L), R(_R) {
        toggled = false;
    }
    void build() {
        a.set_id();
        dual.set_id();
        for (int i = L; i < R; i++) {
            a *= (s[i-L]&1)? B : A;
            dual *= (s[i-L]&1)? A : B;
        }
    }
    void toggle(int l, int r) {
        if (L == l && r == R) {
            toggled ^= 1;
            swap(a, dual);
            return;
        }
        if (toggled) {
            for (int i = L; i < R; i++) {
                if (i < l || i >= r) {
                    s[i-L] ^= 1;
                }
            }
            toggled = false;
        } else {
            for (int i = l; i < r; i++) {
                s[i-L] ^= 1;
            }
        }
        build();
    }
    Matrix<mint> query(int l, int r) {
        if (L == l && r == R) return a;
        Matrix<mint> res;
        for (int i = l; i < r; i++) {
            res *= ((s[i-L]&1) ^ toggled) ? B : A;
        }
        return res;
    }
};

vector<Block> bs;
void update_all(int l, int r) {
    for (int i = l / BLOCK_SIZE; l < r; i++) {
        int _r = min(r, bs[i].R);
        bs[i].toggle(l, _r);
        l = _r;
    }
}
void query_all(int l, int r, mint x, mint y) {
    Matrix<mint> res;
    for (int i = l / BLOCK_SIZE; l < r; i++) {
        int _r = min(r, bs[i].R);
        res *= bs[i].query(l, _r);
        l = _r;
    }
    res.transpose();
    vector<mint> v = {x, y};
    v = res * v;
    cout << v[0] << ' ' << v[1] << "\n";
}

// a direct sqrt impl. 5~6 sec TLE
void solve() {
A.a[1][0] = B.a[0][1] = 1;
    int n, q;
    cin >> n >> q;
    string s; cin >> s;
    for (int i = 0; i < n; i += BLOCK_SIZE) {
        int r = min(i + BLOCK_SIZE, n);
        bs.emplace_back(i, r);
        for (int k = i; k < r; k++) {
            bs.back().s[k-i] = s[k]-'A';
        }
        bs.back().build();
    }

    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int l,r;
            cin >> l >> r;
            l--;
            update_all(l, r);
        } else {
            int l,r,x,y;
            cin >> l >> r >> x >> y;
            l--;
            query_all(l,r,x,y);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
