#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            a[i][j] = s[j]=='.';
        }
    }
    vector<int> R(n, 0), C(m, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            R[i] += a[i][j];
        }
    }
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            C[j] += a[i][j];
        }
    }
    int res = 1e8;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int tmp = R[i]+C[j] - a[i][j];
            res = min(res, tmp);
        }
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--)solve();
    cout << endl;
}
