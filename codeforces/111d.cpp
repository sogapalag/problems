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
}c(1e6);

// [n k]: n into k cycles 
vector<vector<mint>> stir_first(int n) {
    vector<vector<mint>> stir(n+1, vector<mint>(n+1, 0));
    stir[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            stir[i][j] = stir[i-1][j-1] + stir[i-1][j]*(i-1);
        }
    }
    return stir;
}
// {n k}: n into k sets
vector<vector<mint>> stir_second(int n) {
    vector<vector<mint>> stir(n+1, vector<mint>(n+1, 0));
    stir[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            stir[i][j] = stir[i-1][j-1] + stir[i-1][j]*j;
        }
    }
    return stir;
}
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
vector<mint> power_table(mint x, int n) {
    vector<mint> pw(n+1);
    pw[0] = 1;
    for (int i = 1; i <= n; i++) {
        pw[i] = pw[i-1] * x;
    }
    return pw;
}

void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    mint res = 0;
    int lim = min(n,k);
    auto stir2 = stir_second(n);
    vector<mint> way(lim+1); // use exactly x color [n], i.e. stir2[n][x] * x!
    for (int x = 1; x <= lim; x++) {
        mint tmp = 0;
        for (int i = 0; i < x; i++) {
            int sign = (i&1) ? -1 : 1;
            tmp += sign * c.c(x, i) * mint(x-i).exp(n);//log
        }
        way[x] = tmp; //*c.ifac[x]; // color-perm
        //cout << way[x] << ' ';
        //cout << stir2[n][x] <<'\n';
        //assert(way[x] == stir2[n][x]);
    }
    if (m == 1) {
        for (int x = 1; x <= lim; x++) {
            res += c.c(k, x) * way[x];
        }
        assert(res == mint(k).exp(n));
    } else {
        for (int x = 1; x <= lim; x++) {
            for (int d = 0; d <= x; d++) { // diff-color of l,r
                //mint mid = (d==x&&m==2)?
                if (d==x && m>2)continue;
                res += c.c(k, x) * c.c(x, d) * c.c(k-x,d) * way[x]*way[x] * mint(x-d).exp(n*1ll*(m-2));
            }
        }
    }

    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
