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
#define dbg(args...) 2020
#endif

// first note each color, can at most two, -> <-, cannot -> ->
// valid iff any -> & <- don't collide, thus we should iter color, struggle on O(n^3).
//   and once decide set => 1 way,
// solution is fix I as (right-most of ->)
//   then ->/<- is constained on each region, since this ensure no collide
// heavy-impl
void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    vector<vector<int>> pos(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i]; --a[i];
        pos[a[i]].push_back(i);
    }
    vector<int> L(n), R(n);
    for (int i = 0; i < n; i++) {
        L[i] = lower_bound(pos[a[i]].begin(), pos[a[i]].end(), i) - pos[a[i]].begin();
        R[i] = pos[a[i]].size() - L[i] - 1;
    }
    vector<vector<int>> cow(n);
    for (int _ = 0; _ < m; _++) {
        int x, y;
        cin >> x >> y;
        x--;y--;
        cow[x].push_back(y);
    }
    for (int i = 0; i < n; i++) {
        sort(cow[i].begin(), cow[i].end());
    }

    int best = 0; mint res = 0;
    // L, R, x, y, c, C all 0-based
    for (int I = -1; I < n; I++) {
        int C = I == -1 ? -1 : a[I];
        int has = I == -1 ? 0 : 1;
        mint way = 1;
        // check exist
        if (I != -1) {
            auto it = lower_bound(cow[C].begin(), cow[C].end(), L[I]);
            if (it==cow[C].end() || *it != L[I]) continue;
            // add one more right
            it = lower_bound(cow[C].begin(), cow[C].end(), R[I]); // exclude
            int possible = (it - cow[C].begin()) - (R[I] > L[I]); // exclude itself
dbg(L[I], R[I], possible);
            if (possible) {
                has++;
                way *= possible;
            }
        }
dbg(I, C, has);
        for (int c = 0; c < n; c++) if(c!=C){
            int i = lower_bound(pos[c].begin(), pos[c].end(), I) - pos[c].begin();
            // valid if y <= l / y <= r
            int l = i - 1, r = pos[c].size() - i - 1;
dbg(c, i, l, r);
            // l = #valid to put left
            l = upper_bound(cow[c].begin(), cow[c].end(), l) - cow[c].begin();
            r = upper_bound(cow[c].begin(), cow[c].end(), r) - cow[c].begin();
dbg(l, r);
            int x = l*r - min(l,r); // exclude dup. same item both side
            if (x > 0) {
                has += 2;
                way *= x;
            } else if (l+r > 0){
                has += 1;
                way *= l+r;
            }
        }
        if (has > best) {
            best = has;
            res = way;
        } else if (has == best) {
            res += way;
        }
    }
    cout << best << ' ' << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
