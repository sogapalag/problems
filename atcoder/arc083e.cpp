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

const int INF = 0x3f3f3f3f;

void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
        int x; cin >> x; x--;
        g[x].emplace_back(i);
    }
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
//    // anti-chain width <= 2. 
//    // but not for this problem. since X_v is sum of subtree(s). 
//    // so necessary but not sufficient
//    vector<pair<int, int>> bak(n);
//    bak[0] = {a[0], 1<<30};
//    function<bool(int)> dfs = [&](int u){
//        for (int v: g[u]) {
//            bak[v] = bak[u];
//            if (a[v] <= bak[u].first) {
//                bak[v].first = a[v];
//            } else if (a[v] <= bak[u].second) {
//                bak[v].second = a[v];
//            } else return false;
//            if (!dfs(v)) return false;
//        }
//        return true;
//    };
//    auto res = dfs(0)?"POSSIBLE":"IMPOSSIBLE";

#define rep(i) for(int i=0;i<2;i++)
    vector<array<int,2>> sub(n); // sub[i][b] means i has color b^1, min sub sum with color b
    function<bool(int)> dfs = [&](int u){
        for (int v: g[u])
            if (!dfs(v)) return false;
        if (g[u].empty()) return true;
        rep(b){
            int w = b^1;
            vector<vector<int>> dp(2, vector<int>(a[u] + 1, INF));
            int crt = 0;
            dp[crt][0] = 0;
            for (int v: g[u]) {
                int nxt = crt^1;
                for (int i = 0; i <= a[u]; i++) { // dp[crt/nxt] necessary, if not, down is not enough. since [x-0] conflict to below clear.
                    dp[nxt][i] = INF; // clear
                    if (a[v] <= i) { // v as b
                        dp[nxt][i] = min(dp[nxt][i], dp[crt][i-a[v]] + sub[v][w]);
                    }
                    if (sub[v][b] <= i) { // v as w
                        dp[nxt][i] = min(dp[nxt][i], dp[crt][i-sub[v][b]] + a[v]);
                    }
                }
                crt ^= 1;
                dbg(dp);
            }
            int mi = INF;
            for (int i = 0; i <= a[u]; i++) {
                mi = min(mi, dp[crt][i]);
            }
            dbg(u, dp, mi);
            sub[u][w] = mi;
        }
        return sub[u][0] < INF || sub[u][1] < INF;
    };
    auto res = dfs(0)?"POSSIBLE":"IMPOSSIBLE";
    dbg(sub);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
