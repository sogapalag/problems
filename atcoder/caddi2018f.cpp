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

#define rep(i) for(int i=0;i<2;i++)
using pi=pair<int, int>;
using ll=long long;
const int N = 100005; 
int a[N][2];
int b[N][2];
mint dp[2][2][2]; // trk previous two bit
// another method is just count free dimensions.
// first count all a[i][0] freed,
// then check each constraint free-dim -1 if a[i][1] fixed(if not valid, aka all fixed ^!=0, ret 0).
//        if not fixed but has one-wing, +0, not occur, +1
void solve() {
    int n,m;
    cin >> n >> m;
    map<pi,int> cnt;
    map<pi,int> val;
    for (int _ = 0; _ < m; _++) {
        int x,y,z;
        cin >> x >> y >> z;
        if (x > y) swap(x,y);
        cnt[{x,y}]++;
        val[{x,y}] ^= z;
    }
    
    // j-i >= 3 must be 0
    ll Z = n <= 3? 0 : 1ll*(n-3 + 1)*(n-3)/2;
    for (auto& p: cnt) {
        int x,y,z;
        tie(x,y) = p.first;
        z = p.second;
        if (y - x >= 3) {
            if (z == 1) Z--;
            else if (val[p.first] == 0) Z--;
            else {
                cout << 0; return;
            }
        }
    }

    memset(a, -1, sizeof a);
    for (int i = 1; i <= n; i++) {
        if (val.find({i,i}) != val.end()) a[i][0] = val[{i,i}];
    }
    for (int i = 1; i < n; i++) {
        b[i][1] = 2;
        if (val.find({i,i+1}) != val.end()) {
            int z = val[{i,i+1}];
            int c = cnt[{i,i+1}];
            if (c == 2) {
                a[i][1] = z;
            }
            b[i][1] = 1;
        }
    }
    // (i,i+2) must be (i+1,i+1)
    b[1][0] = b[n][0] = 1;
    for (int i = 1; i < n-1; i++) {
        b[i+1][0] = 2;
        if (val.find({i,i+2}) != val.end()) {
            int z = val[{i,i+2}];
            int c = cnt[{i,i+2}];
            if (c == 2) {
                if (a[i+1][0] == -1) {
                    a[i+1][0] = z;
                } else if (a[i+1][0] != z) {
                    cout << 0; return;
                }
            }
            b[i+1][0] = 1;
        }
    }

    if (a[1][0] == -1) {
        dp[0][0][0] = 1;
        dp[0][0][1] = 1;
    } else {
        dp[0][0][a[1][0]] = 1;
    }

    // there are n-1 constraints 
    // . .
    //   .   ^ must be 0
    int crt = 0;
    for (int i = 1; i < n; i++) {
        int nxt = crt ^ 1;
        memset(dp[nxt], 0, sizeof dp[nxt]);
        rep(j)rep(k)rep(l) {
            if (a[i][1] != -1 && a[i][1] != l) continue;
            dp[nxt][k][l] += dp[crt][j][k] * b[i][1];
        }
        swap(crt, nxt);
        memset(dp[nxt], 0, sizeof dp[nxt]);
        rep(j)rep(k)rep(l) {
            if (j^k^l) continue; // ^ != 0
            if (a[i+1][0] != -1 && a[i+1][0] != l) continue;
            dp[nxt][k][l] += dp[crt][j][k] * b[i+1][0];
        }
        crt ^= 1;
    }

    mint res = 0;
    rep(j)rep(k) res += dp[crt][j][k];
    res *= mint(2).exp(Z);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
