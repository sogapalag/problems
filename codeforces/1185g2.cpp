#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007; // 998244353

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

const int N = 51, TT = 2555;
mint dp[N][N][N][3];
mint dp0[N][TT]; // cnt, i个0, make sum t
mint dp12[N][N][TT]; // cnt, j个1, k个2, make sum t

void build_dp(){
    memset(dp, 0, sizeof dp);
    for (int i = 0; i < 3; i++) {
        dp[0][0][0][i] = 1;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                if (i) {
                    dp[i][j][k][1] += dp[i-1][j][k][0];
                    dp[i][j][k][2] += dp[i-1][j][k][0];
                }
                if (j) {
                    dp[i][j][k][0] += dp[i][j-1][k][1];
                    dp[i][j][k][2] += dp[i][j-1][k][1];
                }
                if (k) {
                    dp[i][j][k][0] += dp[i][j][k-1][2];
                    dp[i][j][k][1] += dp[i][j][k-1][2];
                }
            }
        }
    }
}

void solve() {
    int n, T;
    cin >> n >> T;
    vector<int> a(n);
    vector<int> b(n);
    int c[3] = {0,0,0};
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        b[i]--;
        c[b[i]]++; // use for forbid unnessary run
    }
    // combination part. by start/end with [0..2], put next unequal
    build_dp();
    mint fac[N];
    fac[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = fac[i-1] * i;
    }
    auto calc = [&](int x, int y, int z){
        mint r = 0;
        if (x) r += dp[x-1][y][z][0];
        if (y) r += dp[x][y-1][z][1];
        if (z) r += dp[x][y][z-1][2];
        return r * fac[x] * fac[y] * fac[z];
    };

    memset(dp0, 0, sizeof dp0);
    memset(dp12, 0, sizeof dp12);
    dp0[0][0] = 1; dp12[0][0][0] = 1;
    for (int x = 0; x < n; x++) {
        if (b[x] == 0) {
            for (int i = c[0]; i >= 0; i--) {
                for (int t = 0; t < T; t++) {
                    dp0[i+1][t+a[x]] += dp0[i][t];
                }
            }
        } else {
            int _j = b[x]==1;
            int _k = b[x]==2;
            for (int j = c[1]; j >= 0; j--) {
                for (int k = c[2]; k >= 0; k--) {
                    for (int t = 0; t < T; t++) {
                        dp12[j+_j][k+_k][t+a[x]] += dp12[j][k][t];
                    }
                }
            }
        }
    }
    
    mint res = 0;
    for (int i = 0; i <= c[0]; i++) {
        for (int t = 0; t <= T; t++) {
            if (dp0[i][t] == 0) continue;
            for (int j = 0; j <= c[1]; j++) {
                for (int k = 0; k <= c[2]; k++) {
                    if (dp12[j][k][T-t] == 0) continue;
                    mint tmp = dp0[i][t] * dp12[j][k][T-t];
                    tmp *= calc(i, j, k);
                    res += tmp;
                }
            }
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
