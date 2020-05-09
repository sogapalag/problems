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

int n;
mint p;
const int N = 1024; 
mint dp[N][N], sum[N][N];
mint f[N], A[N];

// valid <=k
mint calc(int k) {
    // prep dp
    // dp[i][j]: len=i, row j+1 has bad
    // sum[i][j]: suff >=j
    memset(dp, 0, sizeof dp);
    memset(sum, 0, sizeof sum);
    for (int i = 0; i <= k+1; i++) {
        sum[0][i] = 1;
    }
    for (int i = 1; i <= k; i++) {
        for (int j = k/i; j >= 1; j--) {
            mint P = p.exp(j)*(1-p);
            // iter the first bad pos
            //  => left height >=j+1, right >=j
            for (int l = 0; l < i; l++) {
                dp[i][j] += sum[l][j+1]*sum[i-l-1][j];
            }
            dp[i][j] *= P;
            sum[i][j] = sum[i][j+1] + dp[i][j];
        }
    }
    // linear recurrence
    memset(A, 0, sizeof A);
    memset(f, 0, sizeof f);
    for (int i = 0; i <= k; i++) {
        A[i+1] = sum[i][1]*(1-p);
    }
    k++;
    f[0] = 1;
    for (int i = 1; i <= k; i++) {
        f[i] = sum[i][1];
        for (int j = 1; j <= i; j++) {
            f[i] += A[j]*f[i-j];
        }
    }
    if (n <= k) return f[n];
    // if k ~1e4, ntt. omit.
    //  https://www.luogu.com.cn/problem/solution/P4512
    //  https://www.luogu.com.cn/problem/solution/P4723
    auto convo = [&](auto& x, auto& y){
        int n = x.size();
        int m = y.size();
        vector<mint> z(n+m-1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                z[i+j] += x[i]*y[j];
            }
        }
        // by replace poly x^k = f(x)
        for (int i = n+m-2; i >= k; i--) {
            for (int j = 1; j <= k; j++) {
                z[i-j] += A[j]*z[i];
            }
        }
        while ((int)z.size() > k) z.pop_back();
        return z;
    };
    vector<mint> r{1}, a{0,1}; //r=x^0={1}, a=x={0,1}
    for (int e=n;e;e>>=1){
        if (e&1) {
            r = convo(r,a);
        }
        a = convo(a,a);
    }
    // r = x^n % q(x)
    mint res = 0;
    for (int i = 0; i < (int)r.size(); i++) {
        res += r[i] * f[i];
    }
    return res;
}

// after solve dp, by iter a continous good seg-len i=[0..k], we can a linear-recurrence
// f[n] = A[i]*f[n-i-1]      常系数齐次线性递推
// for speed-up useful links:
//  https://en.wikipedia.org/wiki/Cayley%E2%80%93Hamilton_theorem
//  https://blog.csdn.net/qq_35649707/article/details/78688235
// q(t) = |tI-A|. C-H thm, q(A)=0
// wanna calc A^nx = (A^n % q(A))  多项式取模
//  https://codeforces.com/blog/entry/61306   (elegant version)
// q(x) = x^k - sum_{i=1..k} A[i] x^{k-i} imply x^k = sum (% q(x))
// this G(f) view is much more helpful
//  G(q(x)) = 0
//  a_n = G(x^n) = G(x^n % q(x))
void solve() {
    int m;
    cin >> n >> m;
    int a,b;
    cin >> a >> b;
    p = mint(a)/b;
    cout << calc(m)-calc(m-1) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
