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

const int n = 6;
const int h = 3; 
const int m = 20; // C(6,3)=20
const int R = 1<<n; 
const int MSK = 1<<(n*h); // half edges 
const int MATES = 1<<m;

mint p[n][n];
int mat_mask[m];
mint a[MATES], b[MATES];

// 18 edges, could sat what 3-match, i.e. L=a/b
int find_all_matches(int msk, bool complement) {
    int mates = 0;
    for (int i = 0; i < m; i++) {
        int r = mat_mask[i];
        if (complement) r ^= R-1;
        int v[h];
        for (int _ = 0; _ < h; _++) {
            v[_] = __builtin_ctz(r); r ^= 1<<v[_]; // r &= r-1; // r -= r&-r
        }
        do {
            for (int l = 0; l < h; l++) {
                if (!(msk>>(l*n+v[l]) & 1)) goto next;
            }
            mates |= 1 << i; break;
        next:;
        } while(next_permutation(v, v+h));
    }
    return mates;
}

void solve() {
    for (int i = 0; i < n; i++) {
        p[i][i] = 1;
    }
    int _n; cin >> _n;
    for (int i = 0; i < _n; i++) {
        for (int j = 0; j < _n; j++) {
            cin >> p[i][j]; p[i][j] /= 100;
        }
    }
    for (int r = 0, i = 0; r < R; r++) {
        if (__builtin_popcount(r) == 3) {
            mat_mask[i++] = r;
        }
    }
    // for half edges, each state, contribute a/b[mates]
    for (int msk = 0; msk < MSK; msk++) {
        mint pa = 1, pb = 1;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < n; j++) {
                if (msk>>(i*n+j)&1) {
                    pa *= p[i][j];
                    pb *= p[i+h][j];
                } else {
                    pa *= 1 - p[i][j];
                    pb *= 1 - p[i+h][j];
                }
            }
        }
        int mates = find_all_matches(msk, false);
        int b_mates = find_all_matches(msk, true);
        a[mates] += pa;
        b[b_mates] += pb;
    }
    // notes perfect match iff exist some bit, a/b both set that bit

    // SoS
    for (int i = 0; i < m; i++) {
        for (int mates = 0; mates < MATES; mates++) {
            if (mates>>i&1) {
                b[mates] += b[mates^(1<<i)];
            }
        }
    }

    mint res = 0;
    for (int mates = 0; mates < MATES; mates++) {
        res += a[mates] * b[mates ^ (MATES-1)];
    }
    cout << 1 - res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
