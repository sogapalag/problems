#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007; // 998244353;  998244853; 

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

#define LOCAL
string to_string(string s) { return '"' + s + '"'; }
string to_string(bool x) { return (x ? "T" : "F"); }
string to_string(mint x) { return to_string(int(x)); }
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
#define dbg(args...) 2020
#endif

// should hold transitivity.
using PartialOrd = function<bool(int,int)>;
// f(x, i): x by(<) i
vector<int> get_dominating_left(int n, PartialOrd f) {
    assert(n > 0);
    vector<int> L(n);
    vector<int> stk;
    for (int i = 0; i < n; i++) {
        // some case might need check dominating itself here
        // if not dominating itself, L[i] = i + 1;
        while (!stk.empty() && f(stk.back(), i)) {
            stk.pop_back();
        }
        L[i] = stk.empty() ? 0 : stk.back() + 1;
        stk.push_back(i);
    }
    return L;
}
vector<int> get_dominating_right(int n, PartialOrd f) {
    assert(n > 0);
    vector<int> R(n);
    vector<int> stk;
    for (int i = n-1; i >= 0; i--) {
        // if not dominating itself, R[i] = i - 1;
        while (!stk.empty() && f(stk.back(), i)) {
            stk.pop_back();
        }
        R[i] = stk.empty() ? n-1 : stk.back() - 1;
        stk.push_back(i);
    }
    return R;
}

// first note optim is pick max as peek, one can maintain cost of inc/dec[l,r] in O(n^2). omit
// for larger case, use dominating rule (google has many this kind problems.?!)
//   by maintain cum, e.g. cuml[i] = sum of cost [l..i], for l in [L[i]...i]
//   the key insight, cum has some relation with while we dominated new l,
//   i.e. when we conquer l, obvious [l..i) need to inc. to a[l], := (i-l)*a[l] - sum[l..i)
//      such inc. happened (l - L[l] + 1) times.
// after prep cuml/r L/R
//   cuml occur (R[i]-i+1) times of course
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<mint> sum(n+1);
    for (int i = 0; i < n; i++) {
        sum[i+1] = sum[i] + a[i];
    } 
    vector<mint> cuml(n), cumr(n);
    /*
    auto L = get_dominating_left(n, [&](int l, int i){
            bool yes = a[l] < a[i];
            if (yes) {
                cuml[i] += cuml[l] + a[l]*(i-l) - (sum[i]-sum[l]);
            }
            return yes;
            });
    auto R = get_dominating_right(n, [&](int r, int i){
            bool yes = a[r] <= a[i];
            if (yes) {
                cumr[i] += cumr[r] + a[r]*(r-i) - (sum[r+1]-sum[i+1]);
            }
            return yes;
            });
dbg(L, R);
dbg(cuml,cumr);
    */
    vector<int> L(n), R(n);
    {
        vector<int> stk;
        for (int i = 0; i < n; i++) {
            while (!stk.empty() && a[stk.back()] < a[i]) {
                int l = stk.back();
                cuml[i] += cuml[l] + (a[l]*mint(i-l) - (sum[i]-sum[l])) * (l-L[l]+1);
                stk.pop_back();
            }
            L[i] = stk.empty() ? 0 : stk.back() + 1;
            stk.push_back(i);
        }
    }
    {
        vector<int> stk;
        for (int i = n-1; i >= 0; i--) {
            while (!stk.empty() && a[stk.back()]<=a[i]) {
                int r = stk.back();
                cumr[i] += cumr[r] + (a[r]*mint(r-i) - (sum[r+1]-sum[i+1])) * (R[r]-r+1);
                stk.pop_back();
            }
            R[i] = stk.empty() ? n-1 : stk.back() - 1;
            stk.push_back(i);
        }
    }
    mint res = 0;
    for (int i = 0; i < n; i++) {
        res += cuml[i] * (R[i]-i+1);
        res += cumr[i] * (i-L[i]+1);
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
