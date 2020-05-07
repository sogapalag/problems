#include <bits/stdc++.h>

using namespace std;


// greedy assign 'A' as long as no smaller number achievable and achieving 
//  <=> min of sub both g,rg
//  <=> untrk both g,rg
void solve() {
    int n,m;
    cin >> n >> m;
    vector<vector<int>> g(n), rg(n);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].push_back(y);
        rg[y].push_back(x);
    }
    // cycle?
    vector<int> sta(n);
    function<void(int)> check = [&](int u){
        sta[u] = 1;
        for (int v: g[u]) {
            if (sta[v] == 1) {
                cout << -1; exit(0);// EXIT
            }
            if (sta[v] == 0) {
                check(v);
            }
        }
        sta[u] = 2;
    };
    for (int i = 0; i < n; i++) {
        if (!sta[i]) check(i);
    }

    // sub
    vector<int> dp(n);
    iota(dp.begin(), dp.end(), 0);
    vector<bool> trk(n);
    function<void(int)> dfs = [&](int u){
        trk[u] = true;
        for (int v: g[u]) {
            if (!trk[v]) dfs(v);
            dp[u] = min(dp[u], dp[v]);
        }
    };
    for (int i = 0; i < n; i++) {
        if (!trk[i]) dfs(i);
    }

    // rsub
    vector<int> rdp(n);
    iota(rdp.begin(), rdp.end(), 0);
    vector<bool> rtrk(n);
    function<void(int)> rdfs = [&](int u){
        rtrk[u] = true;
        for (int v: rg[u]) {
            if (!rtrk[v]) rdfs(v);
            rdp[u] = min(rdp[u], rdp[v]);
        }
    };
    for (int i = 0; i < n; i++) {
        if (!rtrk[i]) rdfs(i);
    }
    string res(n, 'E');
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i]==i && rdp[i]==i) { // as min
            ++cnt;
            res[i] = 'A';
        }
    }
    cout << cnt << '\n';
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
