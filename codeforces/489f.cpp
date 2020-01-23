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

const int N = 512; 
//mint dp[2][N][N];

bool ok[N][N];
mint dp[N][N];

mint calc(int i, int j) {
    mint& res = dp[i][j];
    if (ok[i][j]) return res;
    // 0,1 one might find coeff seem on different side from below dp.
    //    but this is correct. both means (i,j)-> (<=)state
    //    calc(i,j):= #fill(i,j)->(0,0)
    //    dp[.][i][j]:= #from (si,sj)->(i,j). 
    if(i&&j)res += calc(i-1, j) * i * j;
    if(i>=2)res += calc(i-2, j+2) * (i*(i-1)/2);
    if(j>=2)res += calc(i, j-2) * (j*(j-1)/2);
    ok[i][j] = true;
    return res;
}

void __solve() {
    int n,m;
    cin >> n >> m >> MOD[0];
    vector<int> cnt(n);
    for (int _ = 0; _ < m; _++) {
        string s; cin >> s;
        for (int i = 0; i < n; i++) {
            cnt[i] += s[i]-'0';
        }
    }
    int c[3] = {};
    for (int x: cnt) c[x]++;

    // bottom-up
    dp[0][0] = 1; ok[0][0] = true;
    cout << calc(c[0],c[1]);

// bottom-down
//    dp[0][c[0]][c[1]] = 1;
//    int lim = c[0] + c[1];
//
//    // explore too many state, O(n^3), just fit in 1s. recursive would be better
//    int crt = 0;
//    for (int _ = 0; _ < n-m; _++) {
//        int nxt = crt^1;
//        memset(dp[nxt], 0, sizeof dp[nxt]);
//        for (int i = 0; i <= c[0]; i++) {
//            for (int j = 0; j+i <= lim; j++) {
//                mint z = dp[crt][i][j];
//                // 0 1
//                if(i&&j) dp[nxt][i-1][j] += z * i * j;
//                // 0 0
//                if(i>=2) dp[nxt][i-2][j+2] += z * (i*(i-1)/2);
//                // 1 1
//                if(j>=2) dp[nxt][i][j-2] += z * (j*(j-1)/2);
//            }
//        }
//        crt ^= 1;
//    }
//    cout << dp[crt][0][0];
}

void solve() {
    int n,m;
    cin >> n >> m >> MOD[0];
    vector<int> cnt(n);
    for (int _ = 0; _ < m; _++) {
        string s; cin >> s;
        for (int i = 0; i < n; i++) {
            cnt[i] += s[i]-'0';
        }
    }
    int c[3] = {};
    for (int x: cnt) c[x]++;

    // no need iter row, i,j already implies which row
    //   i,j this iter-order, ensure dependent value calc-ed
    dp[0][0] = 1;
    int lim = c[0]+c[1];
    for (int i = 0; i <= c[0]; i++) {
        for (int j = 0; j+i <= lim; j++) {
            if(i&&j) dp[i][j] += dp[i-1][j] * i * j;
            if(i>=2) dp[i][j] += dp[i-2][j+2] * (i*(i-1)/2);
            if(j>=2) dp[i][j] += dp[i][j-2] * (j*(j-1)/2);
        }
    }
    cout << dp[c[0]][c[1]];
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
