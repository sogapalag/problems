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
const int N = 3011; 
int pa[N][N], sz[N][N];
ll dp[N][N];

ll calc(int u, int v){
    if (u == v) return 0;
    if (dp[u][v]!=-1) return dp[u][v];
    ll res = sz[u][v]*sz[v][u] + max(calc(pa[v][u], v), calc(pa[u][v], u));
    return dp[u][v] = dp[v][u] = res;
}
// greedy wouln't work. try
// n = 50;
// a = {1, 2, 3, 5, 7, 19, 36, 40, 41, 47, 49}
// greedy would pick 589=19*(50-19), then -> 266=19*(50-36) ... final 1382
// but optimal is pick 504=36*(50-36), then -> 360=36*(50-40) ... final 1525
//   is right sz dec slower, 36 is better coeff.
void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    vector<int> deg(n);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        deg[x]++;
        deg[y]++;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vector<int> leaf;
    for (int i = 0; i < n; i++) {
        if (deg[i]==1)leaf.push_back(i);
    }
dbg(leaf);

    int root;
    function<void(int,int)> dfs = [&](int u, int p){
        pa[root][u] = p;
        sz[root][u] = 0;
        for (int v: g[u])if(v!=p){
            dfs(v,u);
            sz[root][u] += sz[root][v];
        }
        ++sz[root][u];
    };
    for (int i = 0; i < n; i++) {
        dfs(root = i, -1);
    }
    memset(dp, -1, sizeof dp);
    ll res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res = max(res, calc(i,j));
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
