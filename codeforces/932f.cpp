#include <bits/stdc++.h>

using namespace std;

#define LOCAL
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

using ll=long long;

const ll is_query = -(1ll<<62);
struct Line {
    ll k, b;
    Line() {}
    Line(const Line& _r) : k(_r.k), b(_r.b) {}
    Line(ll _k, ll _b) : k(_k), b(_b) {}

    inline ll eval(ll x) const{
        return k*x + b;
    }
    // act like point
    Line& operator-=(const Line& _r) {
        k -= _r.k; b -= _r.b;
        return *this;
    }
    friend Line operator-(const Line& _lhs, const Line& _rhs) {
        return Line(_lhs) -= _rhs;
    }
   // ll cross(const Line& _r) const{
   //     return k*_r.b - b*_r.k;
   // }
    // watch out whether overflow
    inline long double cross(const Line& _r) const{
        return (long double) k*_r.b - (long double) b*_r.k;
    }

    mutable function<const Line* ()> succ;
    
    bool operator < (const Line& _r) const{
        if (_r.b != is_query) return k < _r.k || (k==_r.k && b<_r.b);
        const Line* s = succ();
        if (!s) return false;
        return eval(_r.k) < s->eval(_r.k);
    }
};
struct Hull: public multiset<Line> {// max
    inline bool bad(iterator it) {
        auto z = next(it);
        if (z == end()) return false;
        if (it == begin()) {
            return it->k == z->k;
        }
        auto x = prev(it);
        return (*z - *it).cross(*it - *x) <= 0;
    }
    inline void add_line(ll k, ll b) {
        auto it = insert({k, b});
        if (bad(it)) { erase(it); return; }
        it->succ = [=] { return next(it)==end()? 0: &*next(it); };
        while (next(it) != end() && bad(next(it))) {
            erase(next(it));
        }
        while (it != begin() && bad(prev(it))) {
            erase(prev(it));
        }
    }
    inline ll query(ll x) {
        auto it = lower_bound((Line){x, is_query});
        dbg(it->k, it->b);
        return it->eval(x);
    }
};

void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (auto& x: a) {
        cin >> x;
    }
    for (auto& x: b) {
        cin >> x;
    }
    vector<vector<int>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    vector<int> sz(n), mx(n, -1);
    vector<int> pa(n, -1);
    vector<bool> trk(n, false);
    function<void(int)> get_sz = [&](int u){
        trk[u] = true;
        sz[u] = 1;
        int c = 0, i = -1;
        for (int v: g[u]) {
            if (!trk[v]) {
                pa[v] = u;
                get_sz(v);
                if (sz[v] > c) {
                    c = sz[v];
                    i = v;
                }
                sz[u] += sz[v];
            }
        }
        mx[u] = i;
    };
    get_sz(0);
    
    vector<ll> dp(n);
    vector<Hull*> h(n);
    dbg(a, b);
    function<void(int)> dfs = [&](int u){
        for (int v: g[u]) {
            if (v != pa[u]) {
                dfs(v);
            }
        }
        if (mx[u] == -1) {
            dp[u] = 0;
            h[u] = new Hull;
        } else {
            h[u] = h[mx[u]];
            //swap(h[u], h[mx[u]]);  error
            //h[u] = move(h[mx[u]]); error
            for (int v: g[u]) {
                if (v == pa[u] || v == mx[u]) continue;
                for (auto& line: *h[v]) {
                    h[u]->add_line(line.k, line.b);
                }
            }

            dp[u] = -h[u]->query(a[u]);
        }
        h[u]->add_line(-b[u], -dp[u]);
    };
    dfs(0);
    for (auto& x: dp) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
