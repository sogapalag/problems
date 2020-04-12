#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n;cin >> n;
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
    int r = 0;
    for (int i = 0; i < n; i++) {
        if (deg[i]>1)r=i;
    }

    // min= 1 or 3
    vector<int> arm(n);
    bool could = true;
    function<void(int,int)> check = [&](int u, int p){
        int x = -1;
        for (int v:g[u])if(v!=p){
            check(v,u);
            int tmp = 1 ^ arm[v];
            if (x == -1) x = tmp;
            else if (x != tmp){
                could = false;
            }
        }
        if(x==-1) x = 0;
        arm[u] = x;
    };
    check(r,-1);

    // only direct leaves should same, otherwise we can always maximize by differ
    // since the process is choose any arm[u] for each u
    vector<int> dp(n);
    function<void(int,int)> dfs = [&](int u, int p){
        int cnt = 0;
        for (int v:g[u])if(v!=p){
            dfs(v,u);
            if (deg[v]==1) cnt++;
            dp[u] += dp[v] + 1;
        }
        dp[u] -= max(cnt-1, 0);
    };
    dfs(r,-1);

    cout << (could? 1 : 3) << ' ' << dp[r];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
