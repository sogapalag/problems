#include <bits/stdc++.h>

using namespace std;

const int N = 81; 
const int Z = 80*80*2+10; 
bitset<N*N*4> dp[N][N];
int a[N][N];

void solve() {
    int n,m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x; cin >> x;
            a[i][j] -= x;
            if (a[i][j] < 0) a[i][j]*=-1;
        }
    }
    dp[0][0][Z+a[0][0]] = 1;
    dp[0][0][Z-a[0][0]] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i==0 && j==0)continue;
            if (i) (dp[i][j] |= dp[i-1][j] << a[i][j]) |= dp[i-1][j] >> a[i][j];
            if (j) (dp[i][j] |= dp[i][j-1] << a[i][j]) |= dp[i][j-1] >> a[i][j];
        }
    }
    const int lim  = N*N*2; 
    for (int i = 0; i < lim; i++) {
        if (dp[n-1][m-1][Z+i] || dp[n-1][m-1][Z-i]) {
            cout << i; return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
