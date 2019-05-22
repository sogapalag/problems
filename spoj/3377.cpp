#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n+1);
    while (m--) {
        int x, y;
        cin >> x >> y;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    vector<int> c(n+1, -1);
    auto bfs = [&](){
        for (int i = 1; i <= n; i++) {
            if (~c[i]) continue;
            c[i] = 1;
            queue<int> q;
            q.push(i);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v: g[u]) {
                    if (!~c[v]) {
                        c[v] = c[u] ^ 1;
                        q.push(v);
                    }
                    if (c[v] ==  c[u]) {
                        return false;
                    }
                }
            }
        }
        return true;
    };
    if (bfs()) {
        cout << "No suspicious bugs found!\n";
    } else {
        cout << "Suspicious bugs found!\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Scenario #" << i << ":\n";
        solve();
    }
    cout << endl;
}
