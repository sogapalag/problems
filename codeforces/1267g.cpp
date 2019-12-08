#include <bits/stdc++.h>

using namespace std;

const int N = 101; 
const int C = 1e4+10; 
double dp[N][C]; // #sets, remain r, its sum_r = c

double bino[N][N];

void bino_table() {
    for (int i = 0; i < N; i++) {
        bino[i][0] = 1;
        bino[i][i] = 1;
    }
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < i; j++) {
            bino[i][j] = bino[i-1][j-1] + bino[i-1][j];
        }
    }
}

// note at some stage, remain r items, their sum is c.
//   if random, cost (1/p + 1)* x/2 = (n+r)/r * x/2 = R(r)*r,
//      to buy a average value c/r = B(c)*r.
// it's clear that R < B should random, else should buy.
// then by the fact x <= c_i.
//   thus if R>B we choose to buy, implies R-x/2 = R' > B'=B -c_i still holds.
// i.e. the optimal strategy is that if buy, then rest all should buy.
// now, we can assume the buying order is random too, since order doesn't effect.
// then for any stage, it achieve it with prob = 1 / C(n,r)
// so first knapsack get dp.
// then sum E_r, from r -> r-1, cost
void solve() {
    bino_table();
    int n, X;
    cin >> n >> X;
    int sum = 0;
    dp[0][0] = 1;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x; sum += x;
        for (int r = _; r >= 0; r--) {
            for (int c = 0; c+x <= sum; c++) {
                dp[r+1][c+x] += dp[r][c];
            }
        }
    }

    double res = 0;
    for (int r = 1; r <= n; r++) {
        double E = 0;
        for (int c = 1; c <= sum; c++) {
            E += dp[r][c] * min((double)(n+r)*X/(2*r), (double)c/r);
        }
        res += E / bino[n][r];
    }
    cout << fixed << setprecision(10) << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
