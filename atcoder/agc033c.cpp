#include <bits/stdc++.h>

using namespace std;


// each opration make diamter -1(choose leaf) or -2(chosee non-leaf)
// thus nim-game. diamter == 1 mod 3 lose.
void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n+1);
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    vector<int> d(n+1, -1);
    int md = 0;
    int mu = 1;
    function<void (int)> dfs = [&](int u){
        for (int v: g[u]) {
            if (!~d[v]) {
                d[v] = d[u] + 1;
                if (d[v] > md) {
                    md = d[v];
                    mu = v;
                }
                dfs(v);
            }
        }
    };
    d[1] = 0; dfs(1);
    fill(d.begin(), d.end(), -1);
    d[mu] = 0; dfs(mu);
    if (md%3 == 1) {
        cout << "Second";
    } else {
        cout << "First";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
