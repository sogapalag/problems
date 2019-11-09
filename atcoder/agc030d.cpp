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

const int N = 3003; 
mint dp[2][N][N]; // 0 for >, 1 for =
mint tmp[2][N][N];
#define rep(i) for(int i=0;i<2;i++)
// an elegant version is just use dp[i][j] for >, for i,j pair, not only i>j pair
// then information is enough, and easy to update.
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (a[i] > a[j]) dp[0][i][j] = 1;
            if (a[i] == a[j])dp[1][i][j] = 1;
        }
    }
    auto flip = [&](int& x, int& y){
        dp[0][x][y] = 1 - dp[0][x][y] - dp[1][x][y];
    };
    mint half = mint(1)/2;
    for (int _ = 0; _ < q; _++) {
        int x,y;
        cin >> x >> y;
        x--; y--;
        if (x > y) swap(x, y);
        //memcpy(tmp, dp, sizeof tmp);
        for (int i = 0; i < x; i++) {
            rep(_) {
                //swap(dp[_][i][x], dp[_][i][y]);
                //(dp[_][i][x] += tmp[_][i][x]) *= half;
                //(dp[_][i][y] += tmp[_][i][y]) *= half;
                dp[_][i][x] = dp[_][i][y] = (dp[_][i][x] + dp[_][i][y]) * half;
            }
        }
        //flip(x, y);
        //rep(_)(dp[_][x][y] += tmp[_][x][y]) *= half;
        dp[0][x][y] = (1-dp[1][x][y])*half;
        for (int i = x+1; i < y; i++) {
            //swap(dp[0][x][i], dp[0][i][y]);
            //swap(dp[1][x][i], dp[1][i][y]);
            //flip(x, i);
            //flip(i, y);
            //rep(_) {
            //    (dp[_][x][i] += tmp[_][x][i]) *= half;
            //    (dp[_][i][y] += tmp[_][i][y]) *= half;
            //}
            mint xi = dp[0][x][i] + (1 - dp[1][i][y] - dp[0][i][y]);
            mint iy = dp[0][i][y] + (1 - dp[1][x][i] - dp[0][x][i]);
            dp[0][x][i] = xi * half;
            dp[0][i][y] = iy * half;
            dp[1][x][i] = dp[1][i][y] = (dp[1][x][i] + dp[1][i][y]) * half;
        }
        for (int i = y+1; i < n; i++) {
            rep(_) {
                //swap(dp[_][x][i], dp[_][y][i]);
                //(dp[_][x][i] += tmp[_][x][i]) *= half;
                //(dp[_][y][i] += tmp[_][y][i]) *= half;
                dp[_][x][i] = dp[_][y][i] = (dp[_][x][i] + dp[_][y][i]) * half;
            }
        }
    }
    mint res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            res += dp[0][i][j];
        }
    }
    res *= mint(2).exp(q);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
