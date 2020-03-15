#include <bits/stdc++.h>

using namespace std;
using ll=long long;

template <typename T>
struct Line {
    T k, b;
    int id; // for recover
    Line() {}
    //Line(const Line<T>& _r) : k(_r.k), b(_r.b) {}
    Line(T _k, T _b, int _id) : k(_k), b(_b), id(_id) {}

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
    //vector<Line<T>> hull;
    deque<Line<T>> hull;

    inline void add_line(T k, T b, int id) {
        // k must be monotonic
        Line<T> ln(k, b, id);
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
    inline T __query(T x) {
        int id = bs_last<int>(0, (int)hull.size(), [&](int i){
                if (i == 0) return true;
                return hull[i].eval(x) >= hull[i-1].eval(x);
                });
        return hull[id].eval(x);
    }
    inline pair<T,int> query(T x) {
        int id = bs_last<int>(0, (int)hull.size(), [&](int i){
                if (i == 0) return true;
                return hull[i].eval(x) >= hull[i-1].eval(x);
                });
        return {hull[id].eval(x), hull[id].id};
    }
    // linear
    inline pair<T,int> linear_query(T x) {
        while (hull.size() >= 2) {
            if (hull[0].eval(x) <= hull[1].eval(x)) hull.pop_front();
            else break;
        }
        return {hull[0].eval(x), hull[0].id};
    }

    size_t size() const {
        return hull.size();
    }
    bool empty() const {
        return hull.empty();
    }
};

using Ch=Convex<long long>;

const int N = 100005; 
const int K = 202; 
ll dp[K][N];
int pre[K][N];

// key: cut order doesn't matter, {cut} corresonding profit
//   one can by induction-proof, or just note each pair seg, they splited by exactly one cut. contribute
// one might get relation nxt[i] = max dp[j] + (si - sj)*(n-si), but this si^2, not good.
// better relation nxt[i] = max dp[j] + (si-sj)*sj, i.e. dp[j] repre inside(j) pair-contribution
// keep line id for recover.
// use linear query(since x:sum[i] inc.), elimate log, otherwise last case TLE.
void solve() {
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    vector<ll> sum(n + 1);
    for (int i = 0; i < n; i++) {
        sum[i+1] = sum[i] + a[i];
    }
    //for (int i = 1; i < n; i++) {
    //    dp[0][i] = sum[i] * (sum[n]-sum[i]);
    //}
    for (int _ = 0; _ < k; _++) {
        Ch hull;
        for (int i = 0; i < n; i++) {
            hull.add_line(sum[i], dp[_][i] - sum[i]*sum[i], i);
            ll x;int id;
            tie(x,id) = hull.linear_query(sum[i+1]);
            if (dp[_+1][i+1] < x) {
                dp[_+1][i+1] = x;
                pre[_+1][i+1] = id;
            }
        }
    }
    cout << dp[k][n] << "\n";
    vector<int> res(k);
    for (int _ = k, x = n; _ >= 1; _--) {
        x = pre[_][x];
        res[_-1] = x;
    }
    for (auto& x: res) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
