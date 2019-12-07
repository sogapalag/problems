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
        y-=x;(y+=n)%=n;
        g[x].emplace_back(y);
    }
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        if (!g[i].empty()) {
            int k = g[i].size();
            int mi = *min_element(g[i].begin(), g[i].end());
            a[i] = (k-1)*n + mi;
        }
    }

    for (int i = 0; i < n; i++) {
        int res = 0;
        for (int j = 0; j < n; j++) {
            if (a[j]) {
                int tmp = (j-i+n)%n;
                tmp += a[j];
                res = max(res, tmp);
            }
        }
        cout << res << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
