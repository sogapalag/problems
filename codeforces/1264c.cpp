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

// calc E(i,j):ckpoint i to ckpoint j. in O(1), 
// e.g. E(0,k)*P_k = sum_i={0,..k-1} P_i.  where P_i = P_1*..*P_i
// a quick description, first note there're about 1/P_k rounds, recall geometry trails
// we call if return to 0 or finish at k as one round.
// each step x will hit some point i=[0..k]. consider contribution 1_i
// then for point i, x will hit it with prob P_i in one round. so E_i = Pi/Pk
// that E = sum Pi / Pk
void solve() {
    int n,q;
    cin >> n >> q;
    vector<mint> p(n+1);
    p[0] = 1;
    mint _inv = mint(1)/100;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        p[i] = x * _inv;
        p[i] *= p[i-1];
    }
    vector<mint> sum(n+1), cum(n+1);
    sum[0] = 1;
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i-1] + p[i];
        cum[i] = cum[i-1] + p[i]*i;
    }

    //auto to = [&](int i, int j){
    //    mint x = cum[j-1] - (i>0?cum[i-1]:0);
    //    mint y = sum[j-1] - (i>0?sum[i-1]:0);
    //    mint pos = x - y*(i-1);

    //    x = cum[j] - cum[i];
    //    y = sum[j] - sum[i];
    //    mint neg = x - y*i;
    //    return j-i + (pos-neg)/p[j];
    //};

    // much simpler form than above, don't sum pos/neg first, do (i+1)P_i - iP_i = P_i first
    auto to = [&](int i, int j){
        mint y = sum[j-1] - (i>0?sum[i-1]:0);
        return y / p[j];
    };
    vector<mint> c(n+1);
    c[0] = to(0,n);
    mint res = c[0];
    set<int> s;
    s.insert(0); s.insert(n);
    while (q--) {
        int u; cin >> u; u--;
        if (s.find(u) == s.end()){
            auto it = s.lower_bound(u);
            int r = *it;
            --it;
            int x = *it;
            res -= c[x];
            res += c[x] = to(x, u);
            res += c[u] = to(u, r);
            s.insert(u);
        } else {
            auto it = s.lower_bound(u);
            res -= c[u]; c[u] = 0;
            ++it; int r = *it;
            s.erase(u);
            it = s.lower_bound(u);
            --it;
            int x = *it;
            res -= c[x];
            res += c[x] = to(x, r);
        }
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
