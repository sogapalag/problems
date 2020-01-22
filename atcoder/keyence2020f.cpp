#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;//  998244853; 

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

const int N = 11;
mint c[N][N], ic[N][N];
mint pw[N];
int n,m;
mint row[N][N][3], col[N][N][3];
// remain i x j grid, last op is row[k], use k colors.  k=0, not mean 0-color, just sum for future use
void prep() {
    pw[0] = 1;
    for (int i = 1; i < N; i++) {
        pw[i] = pw[i-1] * 2;
    }
    c[0][0] = ic[0][0] = 1;
    for (int i = 1; i < N; i++) {
        c[i][0] = ic[i][0] = 1;
        for (int j = 1; j < N; j++) {
            c[i][j] = c[i-1][j-1] + c[i-1][j];
            ic[i][j] = 1/c[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        row[i][m][2] = c[n][i] * pw[n-i];
    }
    for (int i = n; i >= 1; i--) {
        for (int j = m; j >= 1; j--) {
            row[i][j][0] = row[i][j][1] + row[i][j][2];
            for (int y = 1; y < j; y++) {
                // if last 2, then allB/W, if last 1, B->W, W->B only one way
                col[i][y][1] += c[j][y] * (2*row[i][j][2] + row[i][j][1]);
                // use exactly 2 colors
                col[i][y][2] += c[j][y] * (pw[j-y] - 2) * row[i][j][2];
            }
            col[i][j][0] = col[i][j][1] + col[i][j][2];
            for (int x = 1; x < i; x++) {
                row[x][j][1] += c[i][x] * (2*col[i][j][2] + col[i][j][1]);
                row[x][j][2] += c[i][x] * (pw[i-x] - 2) * col[i][j][2];
            }
        }
    }
}

// the key idea is consider (time-reverse)
//   i.e. if A ->(ops) B., => \E remove mono row/cols. B->A s.t. remain grid B=A 
// then tricky detail is how to avoid dup-counting. below is (time-reverse) removing
//   suppose 1st start with remove row, use 1/2 colors. and we treat 1as2 for exception only 1st.
//   then next remove col, then row. then col..
//   let k [1/2] be each time #use colors.
//   note k is non-dec.. since if you only use black, next time if k>0 then must be white, 
//      since blacks implies could be taken by 2 round before. and we avoid that for dup-counting.
void solve() {
    cin >> n >> m;
    prep();
    vector<int> R(n), C(m);
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            if (s[j]=='#'){
                R[i] |= 1<<j;
                C[j] |= 1<<i;
            }
        }
    }
    // remove all grid
    mint res = pw[n]; // take all row
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            // end up with use exactly 2 colors 
            // one might argue why cannot be 1 color,
            //  if end k is  .. 2c, 1r.  => last ops can be merged as 2c well.
            //  if end k is  .. 1c, 1r.  => 1c+1r can be op as 2c
            // so idiomic way remove all grid {k} always end with =2.
            res += row[i][j][2] * (pw[j] - 2);
            res += col[i][j][2] * (pw[i] - 2);
        }
    }
    // check remain grid, each row/col should not be mono.
    for (int x = 1; x < 1<<n; x++) {
        for (int y = 1; y < 1<<m; y++) {
            bool mono = false;
            for (int i = 0; i < n; i++) {
                if (x>>i&1) {
                    int rem = R[i]&y;
                    if (rem == 0 || rem == y) mono = true;
                }
            }
            for (int j = 0; j < m; j++) {
                if (y>>j&1) {
                    int rem = C[j]&x;
                    if (rem == 0 || rem == x) mono = true;
                }
            }
            if (mono) continue;
            int i = __builtin_popcount(x);
            int j = __builtin_popcount(y);
            res += (row[i][j][0] + col[i][j][0]) * ic[n][i] * ic[m][j]; // ic since remain specific x,y
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
