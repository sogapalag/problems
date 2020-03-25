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

const int N = 2048; 
const int Z = 3*N; 
mint dp[Z][2*Z];
// key: [x0,x1,x2] if xi>xi+1, then x0,x1 also adj in the perm
//   => perm form:
//              \     #
//           ...      #
//         \          #
//       \            #
//   each '\' size <= 3. and #1 >= #2 (for could merge)
// conclusion: let size be a[...], then #perm := (3n)! / prod_i(sum a[..i])
//   proof: 1/a[..i] := prob to be max among them
// dp[s][d], s=sum a[..i], d = #1 - #2
// Caution: '\' size=3, not only 3,2,1, also 3,1,2
void solve() {
    int n;
    cin >> n >> MOD[0];
    int _n = n*3;
    vector<mint> fac(_n+1);
    vector<mint> ifac(_n+1);
    vector<mint> inv(_n+1);
    auto build = [&](){
        fac[0] = fac[1] = 1;
        ifac[0] = ifac[1] = 1;
        inv[1] = 1;
        for (int i = 2; i <= _n; i++) {
            fac[i] = fac[i-1] * i;
            inv[i] = (-MOD[0]/i) * inv[MOD[0]%i];
            ifac[i] = ifac[i-1] * inv[i];
        }
    };
    build();
    dp[0][Z] = 1;
    for (int s = 0; s < 3*n; s++) {
        for (int d = -3*n; d < 3*n; d++) {
            for (int i:{1,2,3})if(s+i<=3*n) {
                int dd = (i<3?(i==1 ? 1 : -1):0);
                dp[s+i][d+dd+Z] += dp[s][d+Z] * inv[s+i];
            }
        }
    }
    mint res = 0;
    for (int d = 0; d <= 3*n; d++) {
        res += dp[3*n][d+Z];
    }
    res *= fac[3*n];
    cout << res;
}

// conclusion: let i,j,k be #1,#2,#3. #perm := (3n)! / i!j!k!2^j3^k
//    3^k since (3!/2)=3, 2 valid below
// Caution: '\' size=3, not only 3,2,1, also 3,1,2
void solve2() {
    int n;
    cin >> n >> MOD[0];
    int _n = n*3;
    vector<mint> fac(_n+1);
    vector<mint> ifac(_n+1);
    vector<mint> inv(_n+1);
    vector<mint> ipw2(_n+1);
    vector<mint> ipw3(_n+1);
    auto build = [&](){
        fac[0] = fac[1] = 1;
        ifac[0] = ifac[1] = 1;
        inv[1] = 1;
        ipw2[0] = ipw3[0] = 1;
        ipw2[1] = ipw2[0]/2;
        ipw3[1] = ipw3[0]/3;
        for (int i = 2; i <= _n; i++) {
            fac[i] = fac[i-1] * i;
            inv[i] = (-MOD[0]/i) * inv[MOD[0]%i];
            ifac[i] = ifac[i-1] * inv[i];
            ipw2[i] = ipw2[i-1]*ipw2[1];
            ipw3[i] = ipw3[i-1]*ipw3[1];
        }
    };
    build();
    mint res = 0;
    for (int i = 0; i <= 3*n; i++) {
        for (int j = 0; j <= i; j++) {
            int x = i+2*j;
            if (x>3*n) break;
            if (x%3!=0)continue;
            int k = (3*n-x)/3;
            res += ifac[i]*ifac[j]*ifac[k]*ipw2[j]*ipw3[k];
        }
    }
    res *= fac[3*n];
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve2();
    return 0;
}
