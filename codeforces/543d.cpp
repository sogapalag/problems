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

void __solve() {
    int n; cin >> n;
    vector<int> pa(n); pa[0]=-1;
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
        int x; cin >> x; x--;
        pa[i] = x;
        g[x].push_back(i);
    }
    vector<array<mint,2>> dn(n); // [k] any sub path, #bad<=k
    for (int u = n-1; u >= 0; u--) {
        mint x = 1, z = 1;
        for (int v: g[u]){
            x *= dn[v][0] + dn[v][1];
            z *= dn[v][0];
        }
        dn[u][0] = z;
        dn[u][1] = x;
    }
    vector<array<mint,2>> up(n);
    up[0][0] = up[0][1] = 1;
    for (int u = 0; u < n; u++) {
        int m = g[u].size();
        // no divide, might /P=0
        {
            vector<mint> pref(m + 1), suff(m + 1);
            pref[0] = suff[m] = 1; 
            for (int i = 0; i < m; i++) {
                pref[i+1] = pref[i] * dn[g[u][i]][0];
            }
            for (int i = m-1; i >= 0; i--) {
                suff[i] = suff[i+1] * dn[g[u][i]][0];
            }
            for (int i = 0; i < m; i++) {
                int v = g[u][i];
                up[v][0] = up[u][0] * pref[i] * suff[i+1];
            }
        }
        {
            vector<mint> pref(m + 1), suff(m + 1);
            pref[0] = suff[m] = 1; 
            for (int i = 0; i < m; i++) {
                pref[i+1] = pref[i] * (dn[g[u][i]][0] + dn[g[u][i]][1]);
            }
            for (int i = m-1; i >= 0; i--) {
                suff[i] = suff[i+1] * (dn[g[u][i]][0] + dn[g[u][i]][1]);
            }
            for (int i = 0; i < m; i++) {
                int v = g[u][i];
                up[v][1] = up[v][0] + up[u][1] * pref[i] * suff[i+1];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        mint res = dn[i][1] * up[i][1];
        cout << res << ' ';
    }
}

// above dn[.][0] = 1. actually, i.e. all sub be good
void solve() {
    int n; cin >> n;
    vector<int> pa(n); pa[0]=-1;
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
        int x; cin >> x; x--;
        pa[i] = x;
        g[x].push_back(i);
    }
    vector<mint> dn(n); // #bad <= 1
    for (int u = n-1; u >= 0; u--) {
        dn[u] = 1;
        for (int v: g[u]) {
            // 1 means if all sub of v good, then u-v can be bad
            dn[u] *= dn[v] + 1;
        }
    }
    vector<mint> up(n); // #bad <= 1 on uptree
    up[0] = 1;
    for (int u = 0; u < n; u++) {
        int m = g[u].size();
        vector<mint> pref(m + 1), suff(m + 1);
        pref[0] = suff[m] = 1;
        for (int i = 0; i < m; i++) {
            int v = g[u][i];
            pref[i+1] = pref[i] * (dn[v] + 1); // don't forget +1
        }
        for (int i = m-1; i >= 0; i--) {
            int v = g[u][i];
            suff[i] = suff[i+1] * (dn[v] + 1);
        }
        for (int i = 0; i < m; i++) {
            int v = g[u][i];
            // 1 same idea as above
            up[v] = 1 + up[u] * pref[i] * suff[i+1];
        }
    }

    for (int i = 0; i < n; i++) {
        cout << dn[i]*up[i] << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
