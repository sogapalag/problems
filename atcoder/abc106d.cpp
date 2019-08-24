#include <bits/stdc++.h>

using namespace std;

int g[505][505];

void solve() {
    int n,m,q;
    cin >> n >> m >> q;
    while (m--) {
        int x,y;
        cin >> x >> y;
        g[x][y]++;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            g[i][j] += g[i][j-1];
        }
        for (int j = 1; j <= n; j++) {
            g[i][j] += g[i-1][j];
        }
    }
    auto sum = [&](int x,int y,int u, int v){
        return g[u][v] - g[x-1][v]-g[u][y-1]+g[x-1][y-1];
    };
    while (q--) {
        int x,y;
        cin >> x >> y;
        cout << sum(x,x,y,y) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
