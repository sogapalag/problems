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

#define ck(x, p) ((x) & (1<<(p)))

mint dp[22][1<<8][1<<8];
int R[22];

// dp[i][j][k], end state with row i-1, i with j, k each.
void solve() {
    int n, m;
    cin >> n >> m;
    memset(R, 0, sizeof R); // R[n], need to be zero, since last dfs should be same, otherwise different case might error
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            if (s[j] == '#')
                R[i] |= (1<<j);
        }
    }
    const int MSK = 1<<m;
    if (n == 1) {
        cout << (R[0] == MSK-1); return;
    }
    memset(dp, 0, sizeof dp);
    dp[1][R[0]][R[1]] = 1;
    int i, j, k;
    function<void(int,int,int,int)> dfs = [&](int c, int r0, int r1, int r2){
        if (c == m){
            if (r0 == MSK-1) {
                dp[i+1][r1][r2] += dp[i][j][k];
            }
            return;
        }
        if (ck(r0, c)) {
            dfs(c+1, r0, r1, r2);
            return;
        }
        // always top-left be r0 filled
        // ###
        //   #
        if (c+2 < m && !ck(r0, c+1) && !ck(r0, c+2) && !ck(r1, c+2))
            dfs(c+3, r0 | (1<<c) | (1<<(c+1)) | (1<<(c+2)), r1 | (1<<(c+2)), r2);
        // ###
        // #
        if (c+2 < m && !ck(r0, c+1) && !ck(r0, c+2) && !ck(r1, c))
            dfs(c+3, r0 | (1<<c) | (1<<(c+1)) | (1<<(c+2)), r1 | (1<<c), r2);
        // #
        // ###
        if (c+2 < m && !ck(r1, c) && !ck(r1, c+1) && !ck(r1, c+2))
            dfs(c+1, r0 | (1<<c), r1 | (1<<c) | (1<<(c+1)) | (1<<(c+2)), r2);
        //   #
        // ###
        if (c-2 >= 0 && !ck(r1, c) && !ck(r1, c-1) && !ck(r1, c-2))
            dfs(c+1, r0 | (1<<c), r1 | (1<<c) | (1<<(c-1)) | (1<<(c-2)), r2);
        // #
        // #
        // ##
        if (c+1 < m && !ck(r1, c) && !ck(r2, c) && !ck(r2, c+1))
            dfs(c+1, r0 | (1<<c), r1 | (1<<c), r2 | (1<<c) | (1<<(c+1)));
        //  #
        //  #
        // ##
        if (c-1 >= 0 && !ck(r1, c) && !ck(r2, c) && !ck(r2, c-1))
            dfs(c+1, r0 | (1<<c), r1 | (1<<c), r2 | (1<<c) | (1<<(c-1)));
        // ##
        // #
        // #
        if (c+1 < m && !ck(r0, c+1) && !ck(r1, c) && !ck(r2, c))
            dfs(c+2, r0 | (1<<c) | (1<<(c+1)), r1 | (1<<c), r2 | (1<<c));
        // ##
        //  #
        //  #
        if (c+1 < m && !ck(r0, c+1) && !ck(r1, c+1) && !ck(r2, c+1))
            dfs(c+2, r0 | (1<<c) | (1<<(c+1)), r1 | (1<<(c+1)), r2 | (1<<(c+1)));
    };

    for (i = 1; i < n; i++) {
        for (j = 0; j < MSK; j++) {
            for (k = 0; k < MSK; k++) {
                if (dp[i][j][k] == 0) continue;
                dfs(0, j, k, R[i+1]);
            }
        }
    }
    cout << dp[n][MSK-1][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve(), cout << "\n";
    cout << endl;
}
