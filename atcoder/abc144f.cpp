#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].emplace_back(y);
    }
    vector<array<double,2>> e(n);
    e[n-1][0] = 0;
    for (int i = n-2; i >= 0; i--) {
        double sum = 0, mx = 0;
        for (int v: g[i]) {
            sum += e[v][0];
            mx = max(mx, e[v][0]);
        }
        e[i][0] = sum / g[i].size() + 1;
        if (g[i].size() > 1) e[i][1] = (sum-mx)/(g[i].size()-1) + 1;
        else e[i][1] = 1e12;
    }
    double res = min(e[0][0], e[0][1]);
    // consider block i's max children
    for (int i = 0; i < n-1; i++) {
        auto f = e;
        for (int j = i-1; j >= 0; j--) {
            double sum = 0;
            for (int v: g[j]) {
                sum += v==i? f[v][1] : f[v][0];
            }
            f[j][0] = sum / g[j].size() + 1;
        }
        res = min(res, f[0][0]);
    }
    cout << fixed << setprecision(10);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
