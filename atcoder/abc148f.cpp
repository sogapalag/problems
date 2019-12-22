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

void solve() {
    int n, s,t;
    cin >> n >> s >> t;
    s--;t--;
    vector<vector<int>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    // calc two dist[s/t] could be easier
    vector<int> path;
    function<bool(int,int)> get_path = [&](int u,int p){
        path.push_back(u);
        if (u == s) return true;
        for (int v: g[u])if(v!=p){
            if (get_path(v,u)) return true;
        }
        path.pop_back();
        return false;
    };
    get_path(t, -1);
dbg(path);
    int m = path.size();
    int res = (m-1)/2;
    vector<bool> trk(n);
    
    int len = (m+1)/2;
    int root = path[len];
    for (int i = 0; i < len; i++) {
        trk[path[i]] = true;
    }
    function<bool(int,int)> dfs = [&](int u,int depth){
        trk[u] = true;
        int cnt = 0;
        bool has_leaf = false;
        for (int v:g[u])if(!trk[v]){
            cnt++;
            has_leaf |= dfs(v,depth+1);
        }
        if (cnt==0) return true;
        else {
            if (has_leaf) {
                res = max(res, len + depth);
            }
            return false;
        }
    };
    dfs(root, 0);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
