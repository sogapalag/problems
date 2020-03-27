#include <bits/stdc++.h>

using namespace std;

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
    deque<Line<T>> hull;

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
    // linear
    inline T linear_query(T x) {
        while (hull.size() >= 2) {
            if (hull[0].eval(x) <= hull[1].eval(x)) hull.pop_front();
            else break;
        }
        return hull[0].eval(x);
    }
    size_t size() const {
        return hull.size();
    }
    bool empty() const {
        return hull.empty();
    }
};

using Ch=Convex<long long>;
using ll=long long;
// trivial dp. note ^2, but still kx+b, k=k(j), ax^2, a is constant, so treat as ai^2=constant(i)
//   i.e. key: focus on which part is slope k(j)
void solve() {
    int n; cin >> n;
    int A,B,C;
    cin >> A >> B >> C;
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    vector<ll> sum(n + 1);
    for (int i = 0; i < n; i++) {
        sum[i + 1] = sum[i] + a[i];
    }

    Ch hull;
    vector<ll> dp(n + 1);
    for (int i = 0; i < n; i++) {
        hull.add_line(-2*A*sum[i], dp[i] + A*sum[i]*sum[i] - B*sum[i]);
        dp[i + 1] = hull.linear_query(sum[i+1]) + A*sum[i+1]*sum[i+1] + B*sum[i+1] + C;
    }
    cout << dp[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
