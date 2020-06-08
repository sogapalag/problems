#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> A(2*n);
    for (auto& x: A) cin >> x;
    for (int k = 20; k >= 1; k--) {
        const int MSK = 1<<k; 
        auto a = A;
        for (auto& x: a) {
            x &= MSK-1;
        }
        // check eulerian cycle
        vector<vector<int>> g(MSK);
        vector<int> deg(MSK);
        for (int i = 0; i < n; i++) {
            int x = a[i<<1], y = a[i<<1|1];
            deg[x]++; deg[y]++;
            g[x].emplace_back(i);
            g[y].emplace_back(i);
        }

        vector<int> pos(MSK);
        vector<bool> trk(n);
        vector<int> path;
        function<void(int)> dfs = [&](int u){
            for (; pos[u] < g[u].size(); pos[u]++) {
                int i = g[u][pos[u]];
                if (trk[i]) continue;
                trk[i] = true;
                int v = u ^ a[i<<1] ^ a[i<<1|1];
                dfs(v);
                if (u == a[i<<1]) {
                    path.push_back(i<<1|1);
                    path.push_back(i<<1);
                } else {
                    path.push_back(i<<1);
                    path.push_back(i<<1|1);
                }
            }
        };
        for (int x = 0; x < 1<<k; x++) {
            if (deg[x]&1) goto nxt;
        }
        dfs(a[0]);
        if (path.size() != 2*n) {
            goto nxt;
        }
        cout << k << "\n";
        for (int x:path) cout << x+1 << ' ';
        return;
nxt:;
    }
    cout << "0\n";
    for (int i = 1; i <= 2*n; i++) {
        cout << i << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
