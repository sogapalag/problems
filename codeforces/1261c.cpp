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

struct Grid {
    using T = int;
    //using T = long long;
    using G = vector<vector<T>>;
    int n, m;
    G g;
    Grid(int _n, int _m) : n(_n), m(_m) {
        g.resize(n+2);
        for (auto& r: g) {
            r.assign(m+2, 0);
        }
    }
    Grid(const G& _g) : n(_g.size()), m(_g[0].size()) {
        g.resize(n+2);
        for (auto& r: g) {
            r.assign(m+2, 0);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                g[i+1][j+1] = _g[i][j];
            }
        }
    }

    // add diff/delta, after finish add, call build_sum get a[i][j], call again can get sum[i][j]
    // 1-based [l..r)
    void add_rect(int il, int jl, int ir, int jr, T val) {
        g[il][jl] += val;
        g[il][jr] -= val;
        g[ir][jl] -= val;
        g[ir][jr] += val;
    }

    void build_sum() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                g[i][j] += g[i][j-1] - g[i-1][j-1] + g[i-1][j];
            }
        }
    }
    // 0-based [l..r)
    inline T query_sum(int il, int jl, int ir, int jr) {
        return (g[ir][jr] - g[il][jr]) - (g[ir][jl] - g[il][jl]);
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

void solve() {
    int n,m;
    cin >> n >> m;
    vector<vector<int>> _g(n);
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            _g[i].emplace_back(s[j]=='X');
        }
    }
dbg(_g);

    Grid grid(_g);
    grid.build_sum();

    vector<pair<int, int>> res;
    auto ck = [&](int t){
        Grid fire(n,m);
        res.clear();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int il = i-t, jl = j-t;
                int ir = i+t+1, jr = j+t+1;
                // fire source iff
                if (0 <= il && ir <= n && 0 <= jl && jr <= m) {
                    int sum = (ir-il)*(jr-jl);
                    if (grid.query_sum(il,jl,ir,jr) == sum) {
                        res.emplace_back(i,j);
                        fire.add_rect(il+1,jl+1,ir+1,jr+1, 1);
                    }
                }
            }
        }
        fire.build_sum();
dbg(t);
dbg(_g);
dbg(res);
dbg(fire.g);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (_g[i][j] && !fire.g[i+1][j+1]) {
                    return false;
                }
            }
        }
        return true;
    };
    int lim = min({n,m,555});
    int t = 0;
    if (lim > 1) t = bs_last<int>(1, lim, ck);
    ck(t);
    cout << t << "\n";
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        s[i].assign(m, '.');
    }
    for (auto& p: res) {
        s[p.first][p.second] = 'X';
    }

    for (auto& x: s) {
        cout << x << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
