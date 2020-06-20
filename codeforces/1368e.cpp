#include <bits/stdc++.h>

using namespace std;


// delete every depth=2
// note d0:d1:d2 = 1:2:4, by outdeg<=2
void solve() {
    int n,m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        --x,--y;
        g[x].push_back(y);
    }
    vector<int> depth(n);
    vector<int> res;
    for (int i = 0; i < n; i++) {
        if (depth[i] == 2) {
            depth[i] = -1;
            res.push_back(i);
        }
        for (int j:g[i]) {
            depth[j] = max(depth[j], depth[i]+1);
        }
    }

    cout << res.size() << "\n";
    for (auto& x: res) {
        cout << x + 1 << ' ';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
