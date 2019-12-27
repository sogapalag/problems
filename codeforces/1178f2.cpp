#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353; // 998244853;

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

const int N = 1024; 
mint dp[N][N];
mint convoL[N], convoR[N];

void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> c(m);
    for (int i = 0; i < m; i++) {
        cin >> c[i]; --c[i];
    }
    // compress
    vector<int> cut;
    cut.push_back(c[0]);
    for (int i = 1; i < m; i++) {
        if (c[i]!=c[i-1]) cut.push_back(c[i]);
    }
    m = cut.size();
    if (m > 2*n) {
        cout << 0; return;
    }
    vector<int> L(n,-1), R(n,-1);
    vector<vector<int>> pos(n);
    for (int i = 0; i < m; i++) {
        int x = cut[i];
        if (L[x]==-1)L[x] = i;
        R[x] = i;
        pos[x].push_back(i);
    }
    // stk O(n). omit
    for (int col = 0; col < n; col++) {
        int mi = col;
        for (int i = L[col]; i <= R[col]; i++) {
            mi = min(mi, cut[i]);
        }
        if (mi < col) {
            cout << 0; return;
        }
    }

    for (int i = 0; i <= m; i++) {
        dp[i][i] = 1;
    }
    for (int col = n-1; col >= 0; col--) {
        int lin = L[col], rin = R[col] + 1; // at least
        // sub seg ways
        mint mid = 1;
        for (int i = 1; i < pos[col].size(); i++) {
            int l = pos[col][i-1] + 1;
            int r = pos[col][i];
            mid *= dp[l][r];
        }
        // could extend at most
        int lout = lin, rout = rin;
        while (lout>0 && cut[lout-1] > col) {
            lout--;
        }
        while (rout<m && cut[rout] > col) {
            rout++;
        }
        // have to do convo, 3 5|4, 2..2
        // no repetition. since dp as till now, valid paint some min cols as base to the seg.
        // cover all. since |seg|>2 convo could keep split to valid, already covered before.
        for (int l = lout; l <= lin; l++) {
            convoL[l] = 0;
            for (int i = l; i <= lin; i++) {
                convoL[l] += dp[l][i] * dp[i][lin];
            }
        }
        for (int r = rin; r <= rout; r++) {
            convoR[r] = 0;
            for (int i = rin; i <= r; i++) {
                convoR[r] += dp[rin][i] * dp[i][r];
            }
        }
        // above i..i could view as paint col
        // note: dp[l][r], not paint col l..r, is valid splits.
        for (int l = lout; l <= lin; l++) {
            for (int r = rin; r <= rout; r++) {
                dp[l][r] = convoL[l] * mid * convoR[r];
            }
        }
    }
    cout << dp[0][m];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
