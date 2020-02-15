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
        // if k inc. <= 0
        while ((int) hull.size() > 1 && (ln - hull.back()).cross(ln - *(hull.rbegin()+1)) <= 0) {
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
};

using Ch=Convex<long long>;
const int N = 100005; 
ll dp[2][N];
void solve() {
    int n,m,p;
    cin >> n >> m >> p;
    vector<int> a(n);
    for (int i = 1; i < n; i++) {
        cin >> a[i];
        a[i] += a[i-1];
    }
    vector<int> b(m);
    for (int i = 0; i < m; i++) {
        int k,t;
        cin >> k >> t; k--;
        b[i] = t - a[k];
    }
    sort(b.begin(), b.end());
    vector<ll> sum(m+1);
    for (int i = 0; i < m; i++) {
        sum[i+1] = sum[i] + b[i];
    }

    // dp[i] = min_j<i  dp'[j] + (i-j)x - sum_j..i
    memset(dp[0], 0x3f, sizeof dp[0]);
    dp[0][0] = 0;
    int crt = 0;
    p = min(p,m); // test is weak, not include p>m..
    for (int _ = 0; _ < p; _++) {
        int nxt = crt ^ 1;
        memset(dp[nxt], 0x3f, sizeof dp[nxt]);
        Ch ch;
        for (int i = 0; i < m; i++) {
            ch.add_line(i, -dp[crt][i] - sum[i]);
            //ll x = max(0, b[i]);
            ll x = b[i]; //? can < 0..
            dp[nxt][i+1] = -ch.query(x) + (i+1)*x - sum[i+1];
        }
        crt ^= 1;
    }

    cout << dp[crt][m];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
