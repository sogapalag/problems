#include <bits/stdc++.h>

using namespace std;
const int L = 11; 
const int N = 1111; 
char s[N][N];

int R[N][N];
int D[N][N];
int st[N][N][L];


void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> (s[i] + 1);
    }
    
    for (int i = 1; i <= n; i++) {
        int k = 1;
        for (int j = 1; j <= m;) {
            while (j <= k && k <= m && s[i][k] == s[i][j]) {
                k++;
            }
            while (j < k) {
                R[i][j] = k-j;
                j++;
            }
        }
    }
    // sparse
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            st[i][j][0] = R[i][j];
        }
    }
    for (int j = 1; j <= m; j++) {
        for (int k = 1; k < L; k++) {
            for (int i = 1; i + (1<<k) <= n+1; i++) {
                st[i][j][k] = min(st[i][j][k-1], st[i+(1<<(k-1))][j][k-1]);
            }
        }
    }
    auto query = [&](int i, int j, int ii){
        int ss = 31 - __builtin_clz(ii-i);
        return min(st[i][j][ss], st[ii - (1<<ss)][j][ss]);
    };

    for (int j = 1; j <= m; j++) {
        int k = 1;
        for (int i = 1; i <= n;) {
            while (i <= k && k <= n && s[i][j] == s[k][j]) {
                k++;
            }
            while (i < k) {
                D[i][j] = k-i;
                i++;
            }
        }
    }

    long long res = 0;
    for (int j = 1; j <= m; j++) {
        for (int z = 1; z <= n/3; z++) {
            int i = 1, ii, iii;
            while (i + 3*z - 1 <= n) {
                ii = i+z; iii = ii+z;
                if (D[i][j] < z) {
                    i += D[i][j];
                } else if (D[i][j] > z) {
                    i += D[i][j] - z;
                } else {
                    if (D[ii][j] < z) {
                        i = ii + D[ii][j];
                    } else if (D[ii][j] > z) {
                        i = ii + D[ii][j] - z;
                    } else {
                      //  if (s[i][j] == s[iii][j]) {
                      //      i = ii; continue;
                      //  }
                        if (D[iii][j] < z) {
                            i = iii + D[iii][j];
                        } else {
                            res += query(i, j, i+3*z);
                            i = ii;
                        }
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
