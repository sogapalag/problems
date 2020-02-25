#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,k;
    cin >> n >> k;
    vector<bool> leaf(n, true), pa(n, -1);
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
        int x; cin >> x; x--;
        pa[i] = x;
        leaf[x] = false;
        g[x].push_back(i);
    }

    vector<int> once(n), many(n);
    // once[u]: from u explore its sub, best #leaf, without care end
    //    = visit some many, last use once
    // many[u]: must can back to pa[u].
    //    = visit some many, as long as it can take all back to p.
    vector<int> arm(n);
    function<void(int)> dfs = [&](int u){
        if (leaf[u]) {
            once[u] = many[u] = 1;
            return;
        }
        arm[u] = 1e8;
        int delta = 0;
        for (int v:g[u]){
            dfs(v);
            arm[u] = min(arm[u], arm[v] + 1);
            many[u] += many[v];
            delta = max(delta, once[v] - many[v]);
        }
        once[u] = many[u] + delta;
        if (arm[u] >= k) many[u] = 0;
    };
    dfs(0);
    cout << once[0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
