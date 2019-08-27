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
    // sum x = s, x > 0
    mint p(int s, int k) {
        return c(s-1, k-1);
    }
    // sum x = s, x >= 0
    mint z(int s, int k) {
        return p(s+k, k);
    }
    // \E Y-X >= m
    mint hit(int n, int k, int m=1) {
        if (m <= k-n) return c(n+k, n);
        return c(n+k, k-m);
    }
    // catalan trapezoids C_m(n, k)
    // \A Y-X < m,  =c(n+k,n) - hit
    mint cat(int n, int k, int m=1) {
        if (m > k) return c(n+k, n);
        if (m <= k-n) return 0;
        return c(n+k,n) - c(n+k, k-m);
    }
};

const int N = 25004;
const int K = 402; 
mint dp[N][K]; // till i, j = #longest distinct right. we maintain sum, i.e. >=j
mint cnt[N][K];// for distinct A using; maintain # subseq>=m
Comb c(K);
void solve() {
    int n, k, m;
    cin >> n >> k >> m;
    vector<int> a(m);
    for (auto& x: a) {
        cin >> x;
    }
    mint TOT = mint(n-m+1) * mint(k).exp(n-m);
    auto is_col = [&](){
        mt19937 rng(time(0));
        vector<int> hsh(k+1);
        int perm = 0;
        for (int i = 1; i <= k; i++) {
            hsh[i] = rng();
            perm ^= hsh[i];
        }
        int sum = 0;
        for (int i = 0; i < m; i++) {
            sum ^= hsh[a[i]];
            if (i >= k) sum ^= hsh[a[i-k]];
            if (sum == perm) return true;
        }
        return false;
    };
    
    if (m >= k && is_col()) {
        cout << TOT; return;
    }
    int F = m, B = m;
    {
        vector<int> cnt(k+1, 0);
        for (int i = 0; i < m; i++) {
            if (cnt[a[i]]++) {
                F = i; break;
            }
        }
        fill(cnt.begin(), cnt.end(), 0);
        for (int i = m-1; i >= 0; i--) {
            if (cnt[a[i]]++) {
                B = m-i-1; break;
            }
        }
    }
    //cout << F<< '.'<<B << "\n";
    mint res;
    if (F == m) {
        memset(dp, 0, sizeof dp);
        memset(cnt, 0, sizeof cnt);
        dp[1][1] = k; cnt[1][1] = (m==1)? k : 0;
        for (int i = 2; i <= n; i++) {
            for (int j = min(k-1, i); j >= 1; j--) {
                if (j >= 2) {
                    dp[i][j] += (dp[i-1][j-1]-dp[i-1][j]) * (k-j+1);
                    cnt[i][j] += (cnt[i-1][j-1]-cnt[i-1][j]) * (k-j+1);
                }
                dp[i][j] += dp[i-1][j];
                cnt[i][j] += cnt[i-1][j];
                if (j >= m) cnt[i][j] += dp[i][j];
                dp[i][j] += dp[i][j+1];
                cnt[i][j] += cnt[i][j+1];
            }
        }
        res = TOT - cnt[n][1] / c.a(k,m);
    } else {
        vector<mint> pre(n+1), suf(n+1);
        memset(dp, 0, sizeof dp);
        dp[F][F] = 1;
        for (int j = F-1; j >= 1; j--) {
            dp[F][j] += dp[F][j+1];
        }
        pre[F] = dp[F][1];
        for (int i = F+1; i <= n; i++) {
            for (int j = k-1; j >= 1; j--) {
                if (j >= 2)
                    dp[i][j] += (dp[i-1][j-1]-dp[i-1][j]) * (k-j+1);
                dp[i][j] += dp[i-1][j];
                dp[i][j] += dp[i][j+1];
            }
            pre[i] = dp[i][1];
        }
        memset(dp, 0, sizeof dp);
        dp[B][B] = 1;
        for (int j = B-1; j >= 1; j--) {
            dp[B][j] += dp[B][j+1];
        }
        suf[B] = dp[B][1];
        for (int i = B+1; i <= n; i++) {
            for (int j = k-1; j >= 1; j--) {
                if (j >= 2)
                    dp[i][j] += (dp[i-1][j-1]-dp[i-1][j]) * (k-j+1);
                dp[i][j] += dp[i-1][j];
                dp[i][j] += dp[i][j+1];
            }
            suf[i] = dp[i][1];
        }
        int lim = n-m+F;
        mint P = 0;
        for (int i = F; i <= lim; i++) {
            int j = n-m +F+B - i;
            P += pre[i] * suf[j];
        }
        res = TOT - P;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
