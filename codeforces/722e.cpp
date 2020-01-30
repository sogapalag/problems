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
            inv[i] = (-MOD/i) * inv[MOD%i];
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

const int L = 22; 

// when n*m large, O(k^2 L), similar method recall 559c
void solve_large(int n, int m, int k, int X) {
    Comb c(n+m);
    vector<pair<int, int>> a(k);
    for (int i = 0; i < k; i++) {
        int x,y;
        cin >> x >> y;
        a[i] = {x,y};
    }
    sort(a.begin(), a.end());
    if (a.empty() || a.back() != make_pair(n,m)) {
        a.emplace_back(n,m);
        k++;
    } else X -= X/2;
    vector<array<mint,L>> dp(k); // [i][j] #hit i as jth black
    for (int j = 1; j < L; j++) {
        for (int i = 0; i < k; i++) {
            int x,y;
            tie(x,y) = a[i];
            mint tot = c.c(x+y-2, x-1);
            // exclude already hit, now be >=j
            for (int lj = 0; lj < j; lj++) {
                tot -= dp[i][lj];
            }
            // when j<, exclude any pre as j, now be =j
            // j end don't exclude. since >=j now treat as j. X=1
            if(j<L-1)for (int li = 0; li < i; li++) {
                int px,py;
                tie(px,py) = a[li];
                if (px <= x && py <= y) {
                    tot -= dp[li][j] * c.c(x-px+y-py, x-px);
                }
            }
            dp[i][j] = tot;
        }
    }
    mint res = 0;
    for (int j = 1; j < L; j++) {
        //cerr<<j<<' '<<dp.back()[j]<<endl;
        res += dp.back()[j] * X;
        X -= X/2;
    }
    res /= c.c(n+m-2, n-1);
    cout << res;
}

// n*m <= 1e5
void solve() {
    if (0) { // after 20 rounds, x=1
        int x = 1e6;
        int cnt = 0;
        while (x > 1) {
            x -= x/2;
            cnt++;
        }
        cerr<<cnt<<endl;
    }
    int n,m,k,X;
    cin >> n >> m >> k >> X;
    if (n*1ll*m > 100000) {
        solve_large(n,m,k,X);
        return;
    }
    vector<vector<bool>> damn(n+1, vector<bool>(m+1));
    for (int _ = 0; _ < k; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        damn[x][y] = 1;
    }
    vector<vector<array<mint,L>>> dp(n+1, vector<array<mint,L>>(m+1));
    dp[0][0][damn[0][0]] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < L; k++) {
                dp[i+1][j][min(L-1, k + (damn[i+1][j]))] += dp[i][j][k];
                dp[i][j+1][min(L-1, k + (damn[i][j+1]))] += dp[i][j][k];
            }
        }
    }
    mint res = 0;
    for (int k = 0; k < L; k++) {
        res += dp[n-1][m-1][k] * X;
        X -= X/2;
    }
    { //  /=c(N,K)
        int N = n+m-2;
        int K = min(n-1,m-1);
        mint p = 1, q = 1;
        while (K > 0) {
            p *= N - K + 1;
            q *= K--;
        }
        res /= (p/q);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
