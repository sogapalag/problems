#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START convex_hull_roll_back
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
    //__int128_t cross(const Line<T>& _r) {
    //    return (__int128_t)k*_r.b - (__int128_t)b*_r.k;
    //}
    // watch out whether overflow
    inline long double cross(const Line<T>& _r) const{
        return (long double) k*_r.b - (long double) b*_r.k;
    }
};
// Convex hull with roll_back supported
template <typename T>
struct Convex {// max
    int end = 0;
    vector<int> id; // [0..end) is current hull
    vector<int> pos;

    vector<int> pre, pend; // prev id occupied, prev end
    vector<Line<T>> lines; // all pushed lines

    size_t tot() const { return lines.size(); }
    void reserve(int n) {
        id.reserve(n);
        pos.reserve(n);
        pre.reserve(n);
        pend.reserve(n);
        lines.reserve(n);
    }

    Line<T>& hull(int i) {
        return lines[id[i]];
    }

    // O(log)
    void add_line(T k, T b) {
        int n = tot();
        Line<T> ln(k, b);
        // find pos
        int p = end;
        if (p == 1 && ln.k == hull(0).k && ln.b >= hull(0).b) {
            p--;
        }
        if (p > 1) {
            int l = 1, r = p, mid;
            // bs_first
            while (l != r) {
                mid = l + (r-l)/2;
                // k inc <=  /  dec >=
                if ((ln - hull(mid)).cross(ln - hull(mid-1)) <= 0) {
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }
            p = r;
        }
        lines.push_back(ln);
        pos.push_back(p); // pos[n]
        pend.push_back(end);
        if (p < (int)id.size()) {
            pre.push_back(id[p]); // pre[n]
            id[p] = n;
        } else {
            pre.push_back(-1);
            id.push_back(n);
        }
        end = p + 1;
    }

    void roll_back() {
        int n = id[end - 1];
        id[end - 1] = pre[n];
        end = pend[n];
    }

    // O(log)
    T query(T x) {
        int l = 0, r = end;
        assert(l < r);
        // bs_last
        int mid;
        while (l != r) {
            mid = l + (r-l)/2;
            if (mid == 0 || hull(mid).eval(x) >= hull(mid-1).eval(x)) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        return hull(--r).eval(x);
    }
    // WA!!, DO NOT use query_suffix, poped line could still be optimal.
    // unless you ensure there won't be optim. in l...lb(l)
    // correct method: maintain segtree.
    //T query_suffix(int l, T x) {
    //    l = lower_bound(id.begin(), id.begin() + end, l) - id.begin();
    //    return hull(query_id(l, x)).eval(x);
    //}
};

using Ch=Convex<long long>;
// SNIPPETS_END
