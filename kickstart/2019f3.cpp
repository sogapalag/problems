#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// 0:dark
// 1:light
// 2:source
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<vector<int>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    vector<array<ll,3>> dp(n);
    function<void(int,int)> dfs = [&](int u, int p){
        int son = 0;
        for (int v: g[u])if(v!=p){
            dfs(v, u);
            son++;
        }
        if (son == 0) {
            dp[u][0] = 0;
            dp[u][1] = -1ll<<50;
            dp[u][2] = a[u];
            return;
        }

        {// v cannot be 2
            ll sum = 0;
            for (int v: g[u])if(v!=p){
                sum += max(dp[v][0], dp[v][1]);
            }
            dp[u][0] = sum;
        }
        {// some v has to be 2. memo low-change
            ll mi = 1ll<<50;
            ll sum = 0;
            for (int v: g[u])if(v!=p){
                ll mx = max({dp[v][0], dp[v][1], dp[v][2]});
                mi = min(mi, mx - dp[v][2]);
                sum += mx;
            }
            dp[u][1] = sum - mi + a[u];
        }
        {// for dark v, +a[v]
            ll sum = 0;
            for (int v: g[u])if(v!=p){
                ll mx = max({dp[v][0]+a[v], dp[v][1], dp[v][2]});
                sum += mx;
            }
            dp[u][2] = sum + a[u];
        }
    };
    dfs(0,-1);
    ll res = max({dp[0][0], dp[0][1], dp[0][2]});
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
        cout << "\n";
    }
    fflush(stdout);
}
