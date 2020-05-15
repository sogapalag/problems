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

struct PalindromicTree {
    using T = char;
    using Ptr = int;
    T* s; int n;
    vector<array<Ptr,26>> tr;
    vector<Ptr> fail, slink;
    vector<int> len, cnt, sz;
    vector<int> diff;
    vector<mint> dp, g;
    Ptr vc, crt;
    PalindromicTree(T* _s, int _n)
        : s(_s)
        , n(_n)
        , tr(n + 2)
        , fail(n + 2)
        , slink(n + 2)
        , len(n + 2)
        , cnt(n + 2)
        , sz(n + 2)
        , diff(n + 2)
        , dp(n + 1)
        , g(n + 2)
        {
        build();
    }
    void build() {
        fail[0] = 1; len[1] = -1;
        vc = 2; crt = 1;
        s[0] = '$';
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            int c = s[i] - 'a';
            Ptr u = crt;
            while (s[i-len[u]-1] != s[i]) u = fail[u];
            if (!tr[u][c]) {
                Ptr v = fail[u];
                while (s[i-len[v]-1] != s[i]) v = fail[v];
                cnt[vc] = cnt[fail[vc] = tr[v][c]] + 1;
                len[tr[u][c] = vc] = len[u] + 2; // must below, v could = u result fail[vc]=vc.
                diff[vc] = len[vc] - len[fail[vc]];
                slink[vc] = (diff[vc] == diff[fail[vc]] ? slink[fail[vc]] : fail[vc]);
                ++vc;
            }
            crt = tr[u][c];
            ++sz[crt];
            for (int x = crt; x>1; x = slink[x]) {
                g[x] = dp[i - diff[x] - len[slink[x]]]; // include least
                if (diff[x] == diff[fail[x]])
                    g[x] += g[fail[x]];
                dp[i] += g[x];
            }
            if (i&1) dp[i] = 0;
        }
        cout << dp[n];
    }
};
const int N = 1e6+10; 
char s[N];
// first t->s, 0716234. => problem become count Palindrome Partition. each len even.
// technique optim. dp O(n^2)->O(nlogn):
//   https://codeforces.com/blog/entry/19193
//   https://oi-wiki.org/string/pam/#_9      (the image is helpful for understand g calc)
// def: diff[x] = len[x] - len[fail[x]]
//      slink[x] = y s.t. first diff[x] != diff[y] when go-up fail
// since the key pattern. diff is monotonic, and each time differ doubled. so at most log slink.
// def: g[x] = sum dp[i-len[y]], y in [x..slink[x]), i.e. the group with same diff.
void solve() {
    string t; cin >> t;
    int n = t.size();
    for (int i = 0; i < n/2; i++) {
        s[1 + i*2] = t[i];
        s[n - i*2] = t[n/2+i];
    }
    PalindromicTree pt(s, n);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
