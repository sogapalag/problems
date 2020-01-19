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
    // add rect-area each cell val
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
// Sprague–Grundy theorem
// O(n^2 m^2) state, each check O(n+m), whole row/col empty? but keep in mind, answer +=each empty
void solve() {
    int n,m;
    cin >> n >> m;
    vector<string> s(n);
    for (auto& x: s) {
        cin >> x;
    }
    vector<vector<int>> g(n,vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            g[i][j] = s[i][j]=='#';
        }
    }
    Grid grid(g);
    grid.build_sum();
    map<array<int,4>, int> nim;
    int S;
    function<int(int,int,int,int)> mex = [&](int x, int y, int u, int v){
        if (x>=u || y>=v) return 0;
        auto it = nim.find({x,y,u,v});
        if (it != nim.end()) {
            return it->second;
        }
        int cnt = 0;
        set<int> st;
        for (int i = x; i < u; i++) {
            if (grid.query_sum(i, y, i+1, v) == 0) {
                int num = mex(x,y,i,v) ^ mex(i+1,y,u,v);
dbg(x,y,u,v);
dbg(i,num);
                if (num == 0) cnt += v-y; // each in this row
                st.insert(num);
            }
        }
        for (int j = y; j < v; j++) {
            if (grid.query_sum(x, j, u, j+1) == 0) {
                int num = mex(x, y, u, j) ^ mex(x, j+1, u, v);
dbg(x,y,u,v);
dbg(j,num);
                if (num == 0) cnt += u-x; // each
                st.insert(num);
            }
        }
        S = cnt;
        for (int i = 0;;i++){
            if (st.find(i)==st.end()) {
                return nim[{x,y,u,v}] = i;
            }
        }
    };
    mex(0,0,n,m);
    cout << S << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
