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
    __int128_t cross(const Line<T>& _r) {
        return (__int128_t)k*_r.b - (__int128_t)b*_r.k;
    }
    // watch out whether overflow
    //inline long double cross(const Line<T>& _r) const{
    //    return (long double) k*_r.b - (long double) b*_r.k;
    //}
};
// when range [l, r), has property notP~P, want first P.
// when return r, means not found.
template <typename T>
T bs_first(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return r;
}
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
    int end = 0;
    vector<int> id; // store real hull
    vector<int> pos;

    vector<int> pre, pend;
    vector<Line<T>> lines;

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
                if ((ln - hull(mid)).cross(ln - hull(mid-1)) <= 0) {
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }
            p = r;
            //p = bs_first<int>(1, p, [&](int i){
            //        // k inc <=   /  dec >=
            //        return (ln - hull(i)).cross(ln - hull(i-1)) <= 0;
            //        });
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

    int query_id(int l, T x) {
        int first = l, r = end;
        assert(0 <= l && l < r);
        // bs_last
        int mid;
        while (l != r) {
            mid = l + (r-l)/2;
            if (mid == first || hull(mid).eval(x) >= hull(mid-1).eval(x)) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        return r-1;
    }

    T query(T x) {
        return hull(query_id(0, x)).eval(x);
    }
    //T query_suffix(int l, T x) {
    //    l = lower_bound(id.begin(), id.begin() + end, l) - id.begin();
    //    return hull(query_id(l, x)).eval(x);
    //}
};

using Ch=Convex<long long>;
using ll=long long;
// cht problem obviously, there're 2 issues
// 1. ances-chain might vary
// 2. ances-chain query on suffix range
//
// 1. can be solved by roll_back convex,
// 2. note poped lines still might be optim. so difficult query on suffix.
//   solved by use segtree, each node repre. a convex of interval.
//   thus when query, we split suffix into several whole-range convex
void solve() {
    int n, __t;
    cin >> n >> __t;
    vector<int> pa(n);
    vector<ll> w(n), p(n), q(n), lim(n);
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
        cin >> pa[i] >> w[i] >> p[i] >> q[i] >> lim[i];
        --pa[i];
        g[pa[i]].push_back(i);
    }

    vector<ll> dp(n), dis(n);
    vector<ll> tour; tour.reserve(n);
    vector<int> sta(n, -1); int tim = 0;
    // segtree
    int N = 1;
    while (N < n) N *= 2;
    vector<Ch> seg(2*N);
    auto update = [&](int p, int u){
        for (seg[p += N].add_line(dis[u], dp[u]); p >>= 1;) {
            seg[p].add_line(dis[u], dp[u]);
        }
    };
    auto roll_back = [&](int p){
        for (seg[p += N].roll_back(); p >>= 1;) seg[p].roll_back();
    };
    auto query = [&](int l, int r, int u){
        ll res = -1e18;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = max(res, seg[l++].query(p[u]));
            if (r&1) res = max(res, seg[--r].query(p[u]));
        }
        return res - dis[u]*p[u] - q[u];
    };

    function<void(int)> dfs = [&](int u){
        if (u != 0) {
            // depth be seg pos
            int d = lower_bound(tour.begin(), tour.end(), dis[u]-lim[u]) - tour.begin();
            dp[u] = query(d, tour.size(), u);
        }
        update(tour.size(), u);
        sta[u] = tim++;
        tour.push_back(dis[u]);
        for (int v:g[u]) {
            dis[v] = dis[u] + w[v];
            dfs(v);
        }
        tour.pop_back();
        roll_back(tour.size());
    };
    dfs(0);
    for (int i = 1; i < n; i++) {
        cout << -dp[i] << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
