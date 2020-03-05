#include <bits/stdc++.h>

using namespace std;
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
    inline T cross(const Line<T>& _r) const {
        return k*_r.b - b*_r.k;
    }
    // watch out whether overflow
    //inline long double cross(const Line<T>& _r) const{
    //    return (long double) k*_r.b - (long double) b*_r.k;
    //}
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
        // if k inc. <= 0
        while (true) {
            int sz = size();
            if (!sz) break;
            // k might eq
            if (sz == 1) {
                if (ln.k == hull[0].k && ln.b > hull[0].b) {
                    hull.pop_back();
                }
                break;
            } else {
                T c = (ln - hull.back()).cross(ln - *(hull.rbegin()+1));
                if (c >= 0) hull.pop_back();
                else break;
            }
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
    size_t size() const {
        return hull.size();
    }
    bool empty() const {
        return hull.empty();
    }
};

void maxi(ll& x, ll y){
    if (x < y) x = y;
}

using Ch=Convex<long long>;
const ll NINF = -(1e9);// 0xc0c0c0c0'c0c0c0c0; watch out overflow.

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

// the tricky part is handle inner max.
// use d&c, let L[i] R[j] be extend max, from m.
// i.e. if we use a seg [i..j), mx = max(L[i], R[j])
// the key is separte case L[i] <= or >= R[j],
// then we can consider dp[l..m) contribution to nxt[m..r)
// found a bug in Convex Hull template.. when size =1, next k eq, but b les..
void solve() {
    int n,k;
    cin >> n >> k;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<ll> dp(n + 1, NINF), nxt(n + 1);
    dp[0] = 0;

    vector<ll> L(n + 1), R(n + 1);
    function<void(int,int)> divi = [&](int l, int r){
        if (r - l < 2) return;
        int m = (l+r)/2;
        divi(l, m); divi(m, r);
        L[m] = NINF;
        for (int i = m-1; i >= l; i--) {
            L[i] = max(L[i+1], a[i]);
        }
        R[m] = a[m-1];
        for (int i = m+1; i < r; i++) {
            R[i] = max(R[i-1], a[i-1]);
        }
dbg(l, m, r, L, R);

        {// nxt[j] := max_i dp[i] + (i-j) rx
            Ch hull;
            for (int j = m, i = m-1; j < r; j++) {
                while (i >= l && L[i] <= R[j]) {
                    hull.add_line(i, dp[i]);
                    i--;
                }
                if (!hull.empty()) maxi(nxt[j], hull.query(R[j]) - j * R[j]);
            }
        }
        {// nxt[j] := max_i dp[i] + (i-jx) l
            Ch hull;
            for (int j = r-1, i = l; j >= m; j--) {
                while (i < m && L[i] >= R[j]) {
                    // here we use L[i] as k, since it's dec.
                    // note you can use i too, but might need different template, since now i is inc.
                    // but this trigger a bug, since L[i] might equal, when hull size =1, trigger my bug..
                    hull.add_line(L[i], dp[i] + i * L[i]);
                    i++;
                }
                if (!hull.empty()) maxi(nxt[j], hull.query(-j));
            }
        }
    };
    for (int _ = 0; _ < k; _++) {
        fill(nxt.begin(), nxt.end(), NINF);
        divi(0, n+1);
        swap(dp, nxt);
dbg(dp);
    }

    cout << -dp[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
