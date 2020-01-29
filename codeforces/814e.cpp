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

const int N = 51; 
mint dp[2][N][N][N][N];

void solve() {
    int n; cin >> n;
    vector<int> deg(n);
    for (auto& x: deg) {
        cin >> x;
    }
    dp[0][deg[0]==2][deg[0]==3][deg[1]==2][deg[1]==3] = 1;
    int crt = 0;
    for (int u = 2; u < n; u++) {
        int d = deg[u]; d--;
        int nxt = crt ^ 1;
        memset(dp[nxt], 0, sizeof dp[nxt]);
        for (int i = 0; i <= u; i++) {
            for (int j = 0; j <= u && i+j <= u; j++) {
                for (int x = 0; x <= u && i+j+x <= u; x++) {
                    for (int y = 0; y <= u && i+j+x+y <= u; y++) {
                        mint& tmp = dp[crt][i][j][x][y];
                        if (tmp==0) continue;
                        //cerr<<"u:"<<u << ','<<i<<' '<< j << ' '<<x << ' '<< y<<endl;
                        //cerr<<tmp<<endl;
                        // 0
                        if(i) dp[nxt][i-1][j][x + (d==1)][y + (d==2)] += i * tmp;
                        if(j) dp[nxt][i+1][j-1][x + (d==1)][y + (d==2)] += j * tmp;
                        // 1
                        if(i && d && x) dp[nxt][i-1][j][x - 1 + (d>1)][y] += i * x * tmp;
                        if(i && d && y) dp[nxt][i-1][j][x + 1 + (d>1)][y-1] += i * y * tmp;
                        if(j && d && x) dp[nxt][i+1][j-1][x - 1 + (d>1)][y] += j * x * tmp;
                        if(j && d && y) dp[nxt][i+1][j-1][x + 1 + (d>1)][y-1] += j * y * tmp;
                        // 2
                        if(i && d==2 && x>1) dp[nxt][i-1][j][x-2][y] += i * x*(x-1)/2 * tmp;
                        if(i && d==2 && y>1) dp[nxt][i-1][j][x+2][y-2] += i * y*(y-1)/2 * tmp;
                        if(i && d==2 && x && y) dp[nxt][i-1][j][x][y-1] += i * x * y * tmp;
                        if(j && d==2 && x>1) dp[nxt][i+1][j-1][x-2][y] += j * x*(x-1)/2 * tmp;
                        if(j && d==2 && y>1) dp[nxt][i+1][j-1][x+2][y-2] += j * y*(y-1)/2 * tmp;
                        if(j && d==2 && x && y) dp[nxt][i+1][j-1][x][y-1] += j * x * y * tmp;
                        // new level
                        if (i||j) continue; // create new level, prev-deg must empty
                        if(x) dp[nxt][x-1][y][d==1][d==2] += x * tmp;
                        if(y) dp[nxt][x+1][y-1][d==1][d==2] += y * tmp;
                        //if (u==n-1) {
                        //    cerr<<'@'<<dp[nxt][0][0][0][0]<<endl;
                        //}
                    }
                }
            }
        }
        crt ^= 1;
    }
    cout << dp[crt][0][0][0][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
