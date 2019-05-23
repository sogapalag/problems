#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n+1);
    set<pair<int, int>> odd;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
        if (w & 1) {
            odd.emplace(u, v);
            odd.emplace(v, u);
        }
    }
    vector<int> c(n+1, -1);
    auto bfs = [&](){
        queue<int> q;
        q.push(1);
        c[1] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v: g[u]) {
                if (!~c[v]) {
                    if (odd.find(make_pair(u, v)) != odd.end()) {
                        c[v] = c[u] ^ 1;
                    }else{
                        c[v] = c[u];
                    }
                    q.push(v);
                }
            }
        }
    };
    bfs();
    for (int i = 1; i <= n; i++) {
        cout << c[i] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
