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
ll dp[55][1<<20]; // [msk] has(satisfy) black now
// m <= 20, so msk
void solve() {
    int n; cin >> n;
    vector<vector<pair<int,int>>> g(n);
    for (int i = 0; i < n-1; i++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].emplace_back(y,i);
        g[y].emplace_back(x,i);
    }
    vector<int> restricted(n-1); // those conditions contain i
    vector<int> pth;
    int T;
    function<bool(int,int)> dfs = [&](int u, int p){
        for (auto& e: g[u]) {
            int v,i;
            tie(v,i) = e;
            if (v==p) continue;
            pth.push_back(i);
            if (v == T) return true;
            if (!dfs(v, u)) pth.pop_back();
            else return true;
        }
        return false;
    };
    int m; cin >> m;
    for (int j = 0; j < m; j++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        T = y;
        pth.clear();
        dfs(x, -1);
dbg(pth);
        for (int i: pth) {
            restricted[i] |= 1<<j;
        }
    }
dbg(restricted);
    const int MSK = 1<<m; 
    dp[0][0] = 1;
    for (int i = 0; i < n-1; i++) {
        int r = restricted[i];
        for (int msk = 0; msk < MSK; msk++) {
            dp[i+1][msk] += dp[i][msk];
            dp[i+1][msk|r] += dp[i][msk];
        }
    }
    cout << dp[n-1][MSK-1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
