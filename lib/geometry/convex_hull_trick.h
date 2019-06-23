#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START convex_hull
template <typename T>
struct Line {
    T k, b;
    Line() {}
    Line(const Line<T>& _r) : k(_r.k), b(_r.b) {}
    Line(T _k, T _b) : k(_k), b(_b) {}

    T eval(T x) {
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
    long double cross(const Line<T>& _r) {
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

    void add_line(T k, T b) {
        // k must be monotonic
        Line<T> ln(k, b);
        while ((int) hull.size() > 1 && (ln - hull.back()).cross(ln - *(hull.rbegin()+1)) >= 0) {
            hull.pop_back();
        }
        hull.push_back(ln);
    }
    T query(T x) {
        int id = bs_last<int>(0, (int)hull.size(), [&](int i){
                if (i == 0) return true;
                return (hull[i] - hull[i-1]).eval(x) >= 0;
                });
        return hull[id].eval(x);
    }
};

using Ch=Convex<long long>;
// SNIPPETS_END
