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

struct Comb {
    int N;
    vector<mint> fac, ifac, inv;

    Comb(int _n=1) {
        resize(2);
        fac[0] = fac[1] = ifac[0] = ifac[1] = inv[1] = 1;
        N = 1; grow(_n);
    }

    void resize(int _s) {
        fac.resize(_s); ifac.resize(_s); inv.resize(_s);
    }
    bool grow(int _n) {
        if (_n <= N) return false;
        swap(_n, N); resize(N+1);
        for (int i = _n+1; i <= N; i++) {
            fac[i] = fac[i-1] * i;
            inv[i] = (-MOD[0]/i) * inv[MOD[0]%i];
            ifac[i] = ifac[i-1] * inv[i];
        }
        return true;
    }
    // perm
    mint a(int n, int k) {
        if (n < k || k < 0) return 0;
        if (n > N) grow(n);
        return fac[n] * ifac[n-k];
    }
    // choose
    mint c(int n, int k) {
        if (n < k || k < 0) return 0;
        if (n > N) grow(n);
        return fac[n] * ifac[n-k] * ifac[k];
    }
};

const int N = 103;
mint pw[N][N];
mint ex[2][N][N][N];
mint dp[2][N][N][N];

// extreme hard, and 0/1 easy to impl-bug.
// first let f_ij be min of n-m+1 +shape, how to rephrase prod f_ij ?
// suppose original matrix B, and we get matrix f by B. prod is just we fill another matrix A with each <= f_ij
// then <=> row/col-max A <= row/col-min B
// then fix row-max A, col-min B. wlog let A = (1,..,2...3...k..) , B = (1..2..3...)
//
// let k be node of A(k-1 -> k) B(k-1 -> k) conjunction.
// imagine the path walk from (0,0) -> (n,m)
// for A. k -> k+1 shape is like, o,o is k,k+1
//   o------------
//   |    U
//   |---o-------
//   | V |
//   |   |
// for U region, each row indep. can fill [1..=k+1], and at least one =k+1
// for V region, each cell can just fill [1..=k+1]
//
// B is similar dual shape like
//      |   |
//      | U'|
//      |   |
// -----o   |
//   V' |   |
// ---------o
//
// here is another key trick.
// U + V' exactly x rows m cols, i.e. when walkdown, contribute, ex[0].. similar U'+V
//
// so for walk |_, we separate into down/right part. dp[2]
void solve() {
    int n,m,q;
    cin >> n >> m >> q;
    cin >> MOD[0];
    Comb c(N);

    for (int k = 0; k < N; k++) {
        pw[k][0] = 1;
        for (int i = 1; i < N; i++) {
            pw[k][i] = pw[k][i-1] * k;
        }
    }
    for (int k = 1; k <= q; k++) {
        for (int j = 0; j <= m; j++) {
            ex[0][k][0][j] = 1;
            ex[0][k][1][j] = (pw[k][j] - pw[k-1][j]) * pw[q-k+1][m-j];
        }
        for (int i = 2; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                ex[0][k][i][j] = ex[0][k][i-1][j] * ex[0][k][1][j];
            }
        }
        for (int i = 0; i <= n; i++) {
            ex[1][k][i][0] = 1;
            ex[1][k][i][1] = (pw[k][i] - pw[k-1][i]) * pw[q-k+1][n-i];
        }
        for (int i = 0; i <= n; i++) {
            for (int j = 2; j <= m; j++) {
                ex[1][k][i][j] = ex[1][k][i][j-1] * ex[1][k][i][1];
            }
        }

    }
    
    dp[0][0][0][0] = 1;
    for (int k = 0; k < q; k++) {
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                for (int x = 0; x <= n-i; x++) {
                    // careful, dp[1][k]..
                    dp[1][k][i+x][j] += dp[0][k][i][j] * ex[0][k+1][x][m-j] * c.ifac[x];
                }
                for (int y = 0; y <= m-j; y++) {
                    dp[0][k+1][i][j+y] += dp[1][k][i][j] * ex[1][q-k][i][y] * c.ifac[y];
                }
            }
        }
    }
    mint res = dp[0][q][n][m] * c.fac[n] * c.fac[m];
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
