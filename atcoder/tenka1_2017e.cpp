#include <bits/stdc++.h>

using namespace std;

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
#define dbg(args...) 2019
#endif

template <typename T=int>
struct Fenwick {
    int n;
    vector<T> v;
    
    Fenwick(int size = 100005) : n(size), v(n+1, 0) {}
    inline void add(int p, T val) {
        for (; p <= n; p += (p&-p)) { v[p] += val; }
    }
    inline T query(int p) {
        T tmp = 0;
        for (; p > 0; p -= (p&-p)) { tmp += v[p]; }
        return tmp;
    }
    inline T query(int l, int r) {
        return query(r) - query(l-1);
    }
};

// x,y indep. be (N+1)/2 's coord.
// bs on #intersections <= y(x)=x;
// first precomp line by slop, get their y|x=x 's sortness
//  imagine -inf <- y(x) , sortness is (n-1, n-2,...,0). cnt = 0
//  imagine y(x) -> inf, sortness is (0,1,2,...,n-1)     cnt = n*(n-1)/2
//  so we count inversions for sortness
void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n), c(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i] >> c[i];
    }
    const int N = (n)*(n-1)/2;

    double res[2];
    Fenwick<int> st(n);
    for (int _ = 0; _ < 2; _++) {
        //a.emplace_back(0);
        //b.emplace_back(1);
        //c.emplace_back(0);
        vector<int> id(n);
        iota(id.begin(), id.end(), 0);
        sort(id.begin(), id.end(), [&](auto& u, auto& v){
            return (double)a[u]/b[u] > (double)a[v]/b[v];
        });
        dbg(id);
        vector<pair<int, double>> Ys(n);
        auto f = [&](double x){
            int cnt = 0;
            fill(st.v.begin(), st.v.end(), 0);
            for (int i = 0; i < n; i++) {
                int k = id[i];
                double y = (c[k] - a[k]*x)/b[k];
                Ys[i] = {i, y};
            }
            sort(Ys.begin(), Ys.end(), [&](auto& u, auto& v){
                return u.second < v.second || (u.second==v.second && u.first < v.first);
            });
            dbg(x,Ys);
            for (auto& p: Ys) {
                int i = p.first + 1;
                cnt += st.query(i);
                st.add(i, 1);
            }
            dbg(cnt);
            return cnt;
        };
        double l = -1e18, r = 1e18;
        for (int _ = 0; _ < 300; _++) {
            double mid = (l+r)/2;
            if (f(mid) < (N+1)/2) l = mid;
            else r = mid;
        }
        res[_] = l;
        //a.pop_back();
        //b.pop_back();
        //c.pop_back();
        swap(a, b);
    }
    cout << fixed << setprecision(10);
    cout << res[0] << ' ' << res[1] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
