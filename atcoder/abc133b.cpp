#include <bits/stdc++.h>

using namespace std;

int a[22][22];

void solve() {
    int n, d;
    cin >> n >> d;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            cin >> a[i][j];
        }
    }
    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            int sq = 0;
            for (int k = 0; k < d; k++) {
                int dif = a[i][k] - a[j][k];
                sq += dif * dif;
            }
            int dis = sqrt(sq);
            if (dis*dis == sq) res++;
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
