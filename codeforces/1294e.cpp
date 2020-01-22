#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,m;
    cin >> n >> m;
    vector<vector<int>> g(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> g[i][j];--g[i][j];
        }
    }
    int sum = 0;
    for (int j = 0; j < m; j++) {
        // before check each shift, note x, can only contribute equal, to one pos, record cnt.
        vector<int> cnt(n);
        for (int i = 0; i < n; i++) {
            int x = g[i][j];
            if (x%m==j && x/m < n) {
                int I = x/m;
                cnt[(i-I+n)%n]++;
            }
        }
        int mi = n;
        for (int i = 0; i < n; i++) {
            mi = min(mi, i + (n-cnt[i]));
        }
        sum += mi;
    }
    cout << sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
