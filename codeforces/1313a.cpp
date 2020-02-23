#include <bits/stdc++.h>

using namespace std;

int a[8][3];
int sum[1<<8][3];
void prep() {
    for (int i = 1; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            a[i][j] = (i>>j&1);
        }
    }
    for (int m = 0; m < 1<<8; m++) {
        for (int i = 0; i < 8; i++) {
            if (m>>i&1) {
                for (int j = 0; j < 3; j++) {
                    sum[m][j] += a[i][j];
                }
            }
        }
    }
}

// kind of overkill, sort lim, then greedy 1, 2, 3
//  since edge-case is when take 2, facing 1,2,1, cannot a-c first
void solve() {
    int lim[3];
    for (int i = 0; i < 3; i++) {
        cin >> lim[i];
    }
    int res = 0;
    for (int m = 0; m < 1<<8; m++) {
        bool yes = true;
        for (int j = 0; j < 3; j++) {
            if (sum[m][j] > lim[j]) yes = false;
        }
        if(yes) {
            res = max(res, __builtin_popcount(m));
        }
    }
    cout << res-1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    prep();
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
