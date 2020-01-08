#include <bits/stdc++.h>

using namespace std;

const int N = 303; 
double bino[N][N];

void bino_table() {
    for (int i = 0; i < N; i++) {
        bino[i][0] = 1;
        bino[i][i] = 1;
    }
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < i; j++) {
            bino[i][j] = (bino[i-1][j-1] + bino[i-1][j]);
        }
    }
}


// 2^x=(1+1)^x = sum 1_R 1_C
void solve() {
    bino_table();
    int n,m,k;
    cin >> n >> m >> k;
    vector<double> dp(2*n + 2), fall(n*n + 1);
    // (m-x, k-x)/(m,k)=fall[x]
    fall[0] = 1;
    for (int i = 1, x = k, y = m; i <= n*n; i++) {
        fall[i] = fall[i-1];
        fall[i] *= x--;
        fall[i] /= y--;
        if (x <= 0) break;
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            //if (i<n && j==n) continue;
            //if (i==n && j<n) continue;
            int x = n*n - (n-i)*(n-j);
            if (k < x) continue;
            dp[i+j] += fall[x] * bino[n][i] * bino[n][j];
        }
    }
    double res = 0;
    const double LIM = 1e99; 
    for (int i = 0; i <= 2*n; i++) {
        res += dp[i];
        if (res > LIM) {
            cout << "1e99"; return;
        }
    }
    cout << fixed << setprecision(10) << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
