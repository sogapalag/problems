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
#define dbg(args...) 2020
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
        return it->eval(x);
    }
};

struct CentroidDecompositionAutomaton {
    int n;
    vector<vector<int>> g;
    vector<bool> trk;
    vector<int> sz;
    vector<int> centroids_tour;
#define __limit_loop for(int v:g[u])if(!trk[v]&&v!=p)
#define __adj_loop for(int v:g[u])if(v!=p)
    vector<int> a;
    vector<ll> sum, cum;
    CentroidDecompositionAutomaton(int _n)
        : n(_n)
        , g(n)
        , trk(n, false)
        , sz(n)
        , a(n)
        , sum(n)
        , cum(n)
        , sta(n)
        , fin(n)
        , depth(n)
    {
        input();
    }
    inline void add(int u, int v) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        assert(u != v);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    void input() {
        int u, v;
        for (int _ = 1; _ < n; _++) {
            cin >> u >> v;
            u--;v--; // to 0-based
            add(u, v);
        }
        for (auto& x: a) {
            cin >> x;
        }
    }
    int SZ, CEN;
    void find_centroid(int u, int p) {
        sz[u] = 1;
        bool yes = true;
        __limit_loop {
            find_centroid(v, u);
            yes &= sz[v] <= SZ/2;
            sz[u] += sz[v];
        }
        yes &= SZ - sz[u] <= SZ/2;
        if (yes) CEN = u;
    }
    void recalc_sz(int u, int p) {
        sz[u] = 1;
        __limit_loop {
            recalc_sz(v, u);
            sz[u] += sz[v];
        }
    }
    void get_centroids_tour(int u, int p) {
        find_centroid(u, -1);
        trk[u=CEN] = true;
        centroids_tour.push_back(u);
        recalc_sz(u, -1);
        __limit_loop {
            SZ = sz[v];
            get_centroids_tour(v, u);
        }
    }

    void run() {
        centroids_tour.reserve(n);
        SZ = n; get_centroids_tour(0,-1);
        fill(trk.begin(), trk.end(), false);
        res = *max_element(a.begin(), a.end());
        for (int u: centroids_tour) {
            solve(u);
            // from other side, since x/y can be smaller/larger coeff, end.
            reverse(g[u].begin(), g[u].end());
            solve(u);
            trk[u] = true;
        }
        cout << res;
    }

    ll res = 0;
    vector<int> sta, fin, depth;
    vector<int> tour; int tim;
    void dfs(int u, int p) {
        sta[u] = tim++;
        tour.push_back(u);
        __limit_loop {
            // use =, thus we don't need clear
            depth[v] = depth[u] + 1;
            sum[v] = sum[u] + a[v];
            cum[v] = cum[u] + a[v] * 1ll * depth[v];
            dfs(v, u);
        }
        fin[u] = tim;
    }
    // Caution: use __limit_loop to dfs
    void solve(int u) {
        sum[u] = a[u]; depth[u] = 0; cum[u] = 0;
        tour.clear(); tim = 0; dfs(u, -1);
dbg(u, tour);
dbg(sum, cum);
        Hull hull; hull.add_line(1, a[u]);
        // max (dx + 1)sx - cx  +  cy + (sy - au)(dx + 1)
        for (int v: g[u])if(!trk[v]) {
            // (u..y]
            for (int t = sta[v]; t < fin[v]; t++) {
                int x = tour[t]; // y
                // leaf, for constant optim.
                if (sta[x] + 1 == fin[x]) {
                    ll tmp = cum[x] + hull.query(sum[x] - a[u]);
                    res = max(res, tmp);
                }
            }
            // [x..u]
            for (int t = sta[v]; t < fin[v]; t++) {
                int x = tour[t];
                // leaf
                if (sta[x] + 1 == fin[x]) {
                    ll k = depth[x] + 1;
                    hull.add_line(k, k*sum[x] - cum[x]);
                }
            }
        }
        // 2
        // 1 2
        // 2 1
        // i.e. include case u as (larer coeff) end.
        res = max(res, hull.query(0));
    }
#undef __limit_loop
#undef __adj_loop
};

void solve() {
    int n; cin >> n;
    CentroidDecompositionAutomaton cda(n);
    cda.run();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
