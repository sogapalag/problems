#include <bits/stdc++.h>

using namespace std;

const int N = 606; 
int a[N][N], R[N][N], C[N][N];

// x-y must two diag.
// to u-v cheby-coord, must two same row/col, 
// e.g. (u,v) (u,v+k) then another point if above must be (u+k, z) z\in [v,v+k]
void solve() {
    int h, w;
    cin >> h >> w;
    for (int i = 0; i < h; i++) {
        string s; cin >> s;
        for (int j = 0; j < w; j++) {
            if (s[j]=='#') a[i+j][i-j+w] = 1;
        }
    }
    int n = h+w;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            R[i][j+1] = R[i][j] + a[i][j];
            C[i+1][j] = C[i][j] + a[i][j];
        }
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j]) {
                for (int k = 0; k < n; k++) {
                    // all 4 are [..) for avoid dup.
                    if (j+k < n && a[i][j+k]) {
                        res += (i-k<0?0: R[i-k][j+k+1] - R[i-k][j+1]);
                        res += (i+k>=n?0:R[i+k][j+k] - R[i+k][j]);
                    }
                    if (i+k < n && a[i+k][j]) {
                        res += (j-k<0?0: C[i+k][j-k] - C[i][j-k]);
                        res += (j+k>=n?0:C[i+k+1][j+k] - C[i+1][j+k]);
                    }
                }
            }
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
