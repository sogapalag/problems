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

template <typename T>
struct Convex2 {// max
    vector<Line<T>> hull;

    inline void add_line(T k, T b) {
        // k must be monotonic
        Line<T> ln(k, b);
        // if k inc. <= 0
        while ((int) hull.size() > 1 && (ln - hull.back()).cross(ln - *(hull.rbegin()+1)) >= 0) {
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

using Ch2=Convex2<long long>;

void solve() {
    int n; cin >> n;
    vector<int> a(n + 1);
    vector<ll> sum(n + 1);
    ll res = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i-1] + a[i];
        res += a[i] * 1ll * i;
    }
    ll mx = 0;
    {
        Ch ch;
        for (int i = 1; i <= n; i++) {
            ch.add_line(i, -sum[i-1]);
            ll tmp = ch.query(a[i]) - a[i]*1ll*i + sum[i-1];
            mx = max(mx, tmp);
        }
    }

    {
        Ch2 ch;
        for (int i = n; i >= 1; i--) {
            ch.add_line(i, -sum[i]);
            ll tmp = ch.query(a[i]) - a[i]*1ll*i + sum[i]; 
            mx = max(mx, tmp);
        }
    }
    cout << res + mx;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
