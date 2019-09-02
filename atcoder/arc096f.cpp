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

using ll=long long ;

const int N = 51*51*51; 
ll dp[N];

void solve() {
    int n, X,D;
    cin >> n >> X >> D;
    vector<ll> cost(n);
    vector<vector<int>> g(n);
    cin >> cost[0];
    for (int i = 1; i < n; i++) {
        cin >> cost[i];
        int u; cin >> u;u--;
        g[u].emplace_back(i);
    }
    vector<int> sz(n, 1);
    function<void(int)> dfs = [&](int u){
        for (int v: g[u]) {
            dfs(v);
            sz[u] += sz[v];
            cost[u] += cost[v];
        }
    };
    dfs(0);
    dbg(sz,cost);
    memset(dp, 0x3f, sizeof dp);
    dp[0] = 0;
    int lim = n*n*n;
    // note for ratio p<q, final buy(q) cannot more than buy(p), n. (this setting to make q more than p some)
    // since buy sz[q] ps and sz[p] qs, same val but less cost.
    // so pre-comp dp, with each type buy [0..=n] (use log 1,2,4,..).
    for (int i = 0; i < n; i++) {
        int can_buy = i?min(n,D):n;
        int b = 1;
        while (can_buy>0) {
            int c = min(can_buy, b);
            for (int k = lim; k >= c*sz[i]; k--) {
                dp[k] = min(dp[k], dp[k-c*sz[i]] + c*cost[i]);
            }
            can_buy -= c;
            b <<= 1;
        }
    }
    // then for rest, we can greedily. pick most valuables.
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](auto& u, auto& v){
        return sz[u]*cost[v] > sz[v]*cost[u];
    });
    dbg(id);
    ll res = 0;
    for (int k = 0; k <= lim; k++) {
        if (dp[k] > X) continue;
        ll cash = X-dp[k];
        ll val = k;
        dbg(cash, val);
        for (int i: id) {
            int buy = cash/cost[i];
            if (i) buy = min(buy, max(0,D-n));
            cash -= buy*cost[i];
            val += buy*sz[i];
        }
        res = max(res, val);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
