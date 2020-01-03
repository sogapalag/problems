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

const int N = 1024; 
using Bs = bitset<N>;
//Bs basis[55];
//Bs trk;
//int m;
//bool insert_vec(Bs v) {
//    for (int i = 0; i < m; i++) {
//        if (v[i]) {
//            if (!trk[i]) {
//                basis[i] = v;
//                return trk[i] = 1;
//            }
//            v ^= basis[i];
//        }
//    }
//    return false;
//}
//
//void solve() {
//    int n;
//    cin >> m >> n;
//    int must = 0;
//    int cnt = 0;
//    for (int _ = 0; _ < n; _++) {
//        Bs v;
//        string s; cin >> s;
//        for (int i = 0; i < m; i++) {
//            v[i] = s[i]=='1';
//        }
//        int x = v.count();
//        if (x == 0 || x == m) {
//            must++;
//        } else {
//            cnt += insert_vec(v);
//        }
//    }
//    Bs M;
//    for (int i = 0; i < m; i++) {
//        M[i]=1;
//    }
//    cnt += insert_vec(M);
//    cout << cnt << "\n";
//    if (cnt == m) {
//        cout << 1;
//    } else {
//        auto stir2 = stir_second(m+1);
//        mint res = 2;
//        for (int i = 2; cnt+i <= m; i++) {
//            res += stir2[1+m-cnt][i];
//        }
//        cout << res;
//    }
//}
using ll=long long;

// first note by deMorgan, a|b = ~(~a & ~b). also ^ support, | & (~ &)
// note, each par. set repre. one dim.
// above WA since partition might be constraint, those bits are both set with same t.
// so each independent partition.
void solve() {
    int m, n;
    cin >> m >> n;
    auto stir2 = stir_second(m);
    // or use B[n+1] = sum c(n,k)B_k
    vector<mint> bell(m+1);
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= i; j++) {
            bell[i] += stir2[i][j];
        }
    }
    vector<ll> a(m);
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            if (s[j]=='1') a[j] |= 1ll<<i;
        }
    }
    sort(a.begin(), a.end());
    mint res = 1;
    int i = 0, j = 0;
    while (i < m) {
        while (j < m && a[j]==a[i]) {
            j++;
        }
        res *= bell[j-i];
        i = j;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
