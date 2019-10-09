#include <bits/stdc++.h>

using namespace std;

#undef LOCAL
string to_string(string s) { return '"' + s + '"'; }
string to_string(bool x) { return (x ? "T" : "F"); }
string to_string(const char* s) { return to_string((string)s); }
template <typename A, typename B>
string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }
template <typename V>
string to_string(V v) {
    bool f = true; string res = "[";
    for (const auto& x: v) {
        if (!f) res += ", ";
        f = false;
        res += to_string(x); } res += "]";
    return res;
}
void debug() { cerr << endl; }
template <typename H, typename... T>
void debug(H h, T... t) { cerr << " " << to_string(h); debug(t...); }
#ifdef LOCAL
#define dbg(args...) cerr<<"("<<#args<<") =", debug(args)
#else
#define dbg(args...) 2019
#endif

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

// 10
// 1 1 1 1 1 1 3 5 7 2
//
// output: 0
//
// a must be the form, 1..1, 3..3, 7...7, 5..5,... aka continuous-seg. let K be cnt[1]. which implies oprations K-1 times, i.e. cnt[x] <= K
// for seg x..x, let l,x...x,r.  l>x or r<x both implies x's init-pos.
// if both not hold, K-c[x] pos could choose.
// for c[x]=0 nonexist, *= free pos
//
// so key point is how to update free-cnt.
// for a seg x..x,r if x<r we cannot free x's when at x, since min will contagious to r.
// i.e. only when process at r, we can free x's seg. or x>r, we can free x too at x.
//
// but notice when l<x<r. since x<r implies x's init pos may intersect will l's seg. those part cannot free now, i.e. we can only free l to x's init pos.
// since future we can only care x, we can treat modify x's L boarder
void solve() {
    int n; cin >> n;
    vector<int> a(n), b(2*n), c(n, 0);
    for (int i = 0; i < n; i++) {
        int x; cin >> x; x--;
        b[i] = b[i+n] = a[i] = x;
        c[x]++;
    }
dbg("c");
    // no 0
    if (c[0] == 0) {
        cout << 0; return;
    }
    // all 0, n!
    if (c[0] == n) {
        mint res = 1;
        for (int i = 1; i <= n; i++) {
            res *= i;
        }
        cout << res; return;
    }
    // norm
    for (int i = 1; i <= n; i++) {
        if (b[i]==0 && b[i-1]!=0) {
            for (int j = 0; j < n; j++) {
                a[j] = b[i+j];
            }
            break;
        }
    }
dbg(a[0]);
    vector<int> L(n,-1), R(n,-2);
    for (int i = 0; i < n; i++) {
        R[a[i]] = i;
    }
    for (int i = n-1; i >= 0; i--) {
        L[a[i]] = i;
    }
    // not continuous
    for (int i = 0; i < n; i++) {
        if (R[i]-L[i]+1 != c[i]) {
            cout << 0; return;
        }
    }
dbg(L[0],R[0]);
    mint res = 1;
    int fre = 0;
    int K = c[0];
    vector<bool> useoth(n, false);
    for (int x = 0; x < n; x++) {
        //dbg(fre);
        if (c[x] == 0) {
            res *= fre--;
            continue;
        }
        if (c[x] > K) {
            cout << 0; return;
        }
        int l = (L[x]+n-1)%n, r = (R[x]+1)%n;
        l = a[l], r = a[r];
        if (l > x && x < r) {
            if (c[x] != K) {
                cout << 0; return;
            }
            continue;
        }
        if (l < x && x > r) {
            res *= K-c[x]+1;
            fre += c[l] - 1; // + useoth[l];
            fre += c[x] - 1;
            continue;
        }
        if (l > x && x > r) {
            fre += c[x] - 1;
            continue;
        }
        if (l < x && x < r) {
            //fre += c[l] - 1; // + useoth[l];
            //if (c[x] < K) {
            //    useoth[x] = true;
            //    fre--;
            //}
            int new_left = R[x] - K + 1;
            (new_left += n) %= n;
            fre += c[l]-1;
            fre -= L[x] - new_left;
            L[x] = new_left; c[x] = R[x] - L[x] + 1;
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
