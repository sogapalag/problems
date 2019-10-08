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
using ll=long long;

// among two options each, choose first k best diffs
void solve() {
    int n, K;
    cin >> n >> K;
    vector<vector<pair<int,int>>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x,y,w;
        cin >> x >> y >> w;
        x--;y--;
        g[x].emplace_back(y,w);
        g[y].emplace_back(x,w);
    }
dbg(g);
    vector<array<ll,2>> dp(n);
    //  [1] 6   5 [1]
    //  [0] 4   0 [0]
    //  5+4 > 6+0
    //function<void(int,int)> dfs = [&](int u, int p){
    //    dbg(u);
    //    {
    //        priority_queue<pair<ll, int>> pq;
    //        for (auto &_: g[u]) {
    //            int v,w;
    //            tie(v,w) = _;
    //            if (v == p) continue;
    //            dfs(v, u);
    //            pq.emplace(dp[v][0], v<<1);
    //            pq.emplace(dp[v][1] + w, v<<1|1);
    //        }
    //        int cnt = 0;
    //        ll sum = 0;
    //        while (!pq.empty()) {
    //            ll val; int v;
    //            tie(val, v) = pq.top(); pq.pop();
    //        dbg(val, v);
    //            if (trk[v>>1]) continue;
    //            if ((v&1) && cnt >= K) continue;
    //            sum += val;
    //            if (v&1) cnt++;
    //            trk[v>>1] = true;
    //        }
    //        dp[u][0] = sum;
    //    }
    //    {
    //        priority_queue<pair<ll, int>> pq;
    //        for (auto &_: g[u]) {
    //            int v,w;
    //            tie(v,w) = _;
    //            if (v == p) continue;
    //            trk[v] = false;
    //            pq.emplace(dp[v][0], v<<1);
    //            pq.emplace(dp[v][1] + w, v<<1|1);
    //        }
    //        int cnt = 0;
    //        ll sum = 0;
    //        while (!pq.empty()) {
    //            ll val; int v;
    //            tie(val, v) = pq.top(); pq.pop();
    //        dbg(val, v);
    //            if (trk[v>>1]) continue;
    //            if ((v&1) && cnt >= K-1) continue;
    //            sum += val;
    //            if (v&1) cnt++;
    //            trk[v>>1] = true;
    //        }
    //        dp[u][1] = sum;
    //    }
    //};
    function<void(int,int)> dfs = [&](int u, int p){
        ll base = 0;
        vector<ll> diffs;
        for (auto& _: g[u]) {
            int v,w;
            tie(v,w) = _;
            if (v == p) continue;
            dfs(v, u);
            base += dp[v][0];
            diffs.emplace_back(dp[v][1] + w - dp[v][0]);
        }
        sort(diffs.begin(), diffs.end(), greater<ll>());
        int lim = min(K, (int)diffs.size());
        dp[u][0] = base;
        for (int i = 0; i < lim; i++) {
            if (diffs[i] > 0) dp[u][0] += diffs[i];
        }
        lim = min(K-1, (int)diffs.size());
        dp[u][1] = base;
        for (int i = 0; i < lim; i++) {
            if (diffs[i] > 0) dp[u][1] += diffs[i];
        }
    };
    dfs(0,-1);
dbg(dp);
    ll res = max(dp[0][0], dp[0][1]);
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
