#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, m, h;
    cin >> n >> m >> h;
    vector<int> a(m+1);
    vector<int> b(n+1);
    vector<vector<int>> d(n+1, vector<int>(m+1));
    for (int i = 1; i <= m; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int x; cin >> x;
            d[i][j] = x? min(b[i], a[j]) : 0;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << d[i][j] << ' ';
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
