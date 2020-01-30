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
// using, x^n = sum_{k:0..=n} {n k} (x)_k
// (x)_n := x*(x-1)...(x-n+1)
vector<mint> fall_table(int x, int n) {
    vector<mint> res(n+1);
    res[0] = 1;
    for (int i = 1; i <= n; i++) {
        res[i] = res[i-1] * (x-i+1);
    }
    return res;
}
vector<mint> rise_table(int x, int n) {
    vector<mint> res(n+1);
    res[0] = 1;
    for (int i = 1; i <= n; i++) {
        res[i] = res[i-1] * (x+i-1);
    }
    return res;
}

const int N = 5022; 
mint dp[N][N];
mint rec[2][N];

void solve() {
    int n,m;
    cin >> n >> m >> MOD[0];
    dp[1][1] = 1;
    for (int i = 1; i < N-1; i++) {
        for (int j = 1; j < N-1; j++) {
            dp[i+1][j+1] += dp[i][j];
            dp[i+1][j] += dp[i][j] * (j-1);
        }
    }
    auto fall = fall_table(m, N);
    auto fac = rise_table(1, N);
    
    rec[0][0] = 1;
    mint sum = 1;
    int crt = 0;
    for (int _ = 0, pre_len = 0; _ < n; _++) {
        int len; cin >> len;
        int nxt = crt ^ 1;
        for (int j = 1; j <= len; j++) {
            rec[nxt][j] += sum * dp[len][j] * fall[j];
            rec[nxt][j] -= rec[crt][j] * dp[len][j] * fac[j];
        }
        // clear & update
        memset(rec[crt], 0, 4*(pre_len+1)); pre_len = len;
        sum = 0;
        for (int j = 1; j <= len; j++) {
            sum += rec[nxt][j];
        }
        crt ^= 1;
    }
    cout << sum;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
