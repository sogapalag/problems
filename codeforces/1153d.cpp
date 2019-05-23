#include <bits/stdc++.h>

using namespace std;


// dp[u], #minimum needed modified leaves to increas u.
// thus, if u max, the minimal dp of children. if min, the sum of dp of children.
// note since we greedily put largest number in those leaves.
void solve() {
    int n; cin >> n;
    vector<int> op(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> op[i];
    }
    vector<vector<int>> g(n+1);
    for (int i = 2; i <= n; i++) {
        int x; cin >> x;
        g[x].emplace_back(i);
    }
    function<pair<int,int> (int)> dfs = [&](int u) -> pair<int,int>{
        if (g[u].empty()) {
            return {1, 1};
        }
        int lef = 0;
        int dp = op[u]? 1e6: 0;
        for (int v: g[u]) {
            pair<int, int> p = dfs(v);
            int x = p.first;
            int y = p.second;
            lef += x;
            if (op[u]) {
                dp = min(dp, y);
            } else {
                dp += y;
            }
        }
        return {lef, dp};
    };
    pair<int, int> p = dfs(1);
    int res = p.first - p.second + 1;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
