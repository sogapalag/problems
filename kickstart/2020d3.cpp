#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    int D[2];
    cin >> D[0] >> D[1];
    vector<int> pa(n,-1);
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
        cin >> pa[i]; --pa[i];
        g[pa[i]].push_back(i);
    }
    vector<array<int,2>> cnt(n);
    double res = 0;
    function<void(int,int)> dfs = [&](int u,int d){
        int x = cnt[d%D[0]][0];
        int y = cnt[d%D[1]][1];
        ++cnt[d%D[0]][0];
        ++cnt[d%D[1]][1];
        for (int v: g[u]) {
            dfs(v, d+1);
        }
        // subtree #node with same module depth
        x = cnt[d%D[0]][0] - x;
        y = cnt[d%D[1]][1] - y;
        res += 1 - double(n-x)/n * double(n-y)/n;
    };
    dfs(0,0);
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(10);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
