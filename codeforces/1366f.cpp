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
using ll=long long;

template <typename T>
struct Line {
    T k, b;
    Line() {}
    Line(const Line<T>& _r) : k(_r.k), b(_r.b) {}
    Line(T _k, T _b) : k(_k), b(_b) {}

    inline T eval(T x) const{
        return k*x + b;
    }
    // act like point
    Line<T>& operator-=(const Line<T>& _r) {
        k -= _r.k; b -= _r.b;
        return *this;
    }
    friend Line<T> operator-(const Line<T>& _lhs, const Line<T>& _rhs) {
        return Line<T>(_lhs) -= _rhs;
    }
   // T cross(const Line<T>& _r) {
   //     return k*_r.b - b*_r.k;
   // }
    // watch out whether overflow
    inline long double cross(const Line<T>& _r) const{
        return (long double) k*_r.b - (long double) b*_r.k;
    }
};

// when range [l, r), has property P~notP, want last P.
// when return l-1, means not found.
template <typename T>
T bs_last(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            l = mid + 1;
        }else {
            r = mid;
        }
    }
    return r-1;
}
template <typename T>
struct Convex {// max
    vector<Line<T>> hull;

    inline void add_line(T k, T b) {
        // k must be monotonic
        Line<T> ln(k, b);
        // special case, otherwise intrinsic bug.
        if (size() == 1 && ln.k == hull[0].k && ln.b >= hull[0].b) {
            hull.pop_back();
        }
        // if k inc. <= 0
        while (size() > 1 && (ln - hull.back()).cross(ln - *(hull.rbegin()+1)) <= 0) {
            hull.pop_back();
        }
        hull.push_back(ln);
    }
    inline T query(T x) {
        int id = bs_last<int>(0, (int)hull.size(), [&](int i){
                if (i == 0) return true;
                return hull[i].eval(x) >= hull[i-1].eval(x);
                });
        return hull[id].eval(x);
    }
    inline int query_id(T x) {
        int id = bs_last<int>(0, (int)hull.size(), [&](int i){
                if (i == 0) return true;
                return hull[i].eval(x) >= hull[i-1].eval(x);
                });
        return id;
    }
    // linear, replace with deque
    //inline T linear_query(T x) {
    //    while (hull.size() >= 2) {
    //        if (hull[0].eval(x) <= hull[1].eval(x)) hull.pop_front();
    //        else break;
    //    }
    //    return hull[0].eval(x);
    //}
    size_t size() const {
        return hull.size();
    }
    bool empty() const {
        return hull.empty();
    }
};

using Ch=Convex<long long>;

const int N = 2048; 
int dp[N][N]; // dp[v][k]: end with v, in k step

// key: last edge of path is max of path, since we can always repeat end edge
//    i.e. optim-form = a simple path + repeat edge
//  => when len >= m, => \E repeat edge, => the edge must be the repeat-end-max edge
//  => construct convex hull of at most n lines
//   => bs each line's range x
void solve() {
    int n,m,q;
    cin >> n >> m >> q;
    vector<tuple<int,int,int>> es(m);
    vector<int> nei(n);
    for (int i = 0; i < m; i++) {
        int x,y,z;
        cin >> x >> y >> z;
        --x,--y;
        es[i] = {x,y,z};
        nei[x] = max(nei[x], z);
        nei[y] = max(nei[y], z);
    }
    memset(dp, 0xc0, sizeof dp);
    dp[0][0] = 0;
    for (int i = 0; i < m; i++) {
        for (auto [u,v,w]: es) {
            dp[u][i+1] = max(dp[u][i+1], dp[v][i] + w);
            dp[v][i+1] = max(dp[v][i+1], dp[u][i] + w);
        }
    }
    //vector<pair<int, int>> lines(n);
    //for (int i = 0; i < n; i++) {
    //    lines[i] = {nei[i], dp[i][m] - m*nei[i]};
    //}
    vector<pair<int, int>> lines;
    for (int i = 0; i < n; i++) {
        if (dp[i][m] > 0) {
            lines.emplace_back(nei[i], dp[i][m] - m*nei[i]);
        }
    }
    sort(lines.begin(), lines.end());
    Ch ch;
    for (auto [k,b]: lines) {
        ch.add_line(k, b);
    }
    mint res = 0;
    for (int i = 1; i < m; i++) {
        int mx = 0;
        for (int u = 0; u < n; u++) {
            mx = max(mx, dp[u][i]);
        }
        res += mx;
    }
    for (int i = 0, l = m; i < ch.size(); i++) {
        if (l > q) break;
        int r = bs_last<int>(l, q+1, [&](int r){
                return ch.query_id(r) == i;
                });
        ++r;
        ll k = ch.hull[i].k;
        ll b = ch.hull[i].b;
        res += (k*mint(r-l)*(r+l-1))/2 + mint(r-l)*b;
        l = r;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
