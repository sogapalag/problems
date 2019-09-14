#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> open(n);
    for (int i = 0; i < n; i++) {
        int x = 0;
        for (int j = 0; j < 10; j++) {
            int k; cin >> k;
            x |= k<<j;
        }
        open[i] = x;
    }
    vector<array<int,11>> p(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= 10; j++) {
            cin >> p[i][j];
        }
    }
    int mx = -2e9;
    for (int msk = 1; msk < (1<<10); msk++) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            int k = __builtin_popcount(msk & open[i]);
            sum += p[i][k];
        }
        mx = max(mx, sum);
    }
    cout << mx;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
