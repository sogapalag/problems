#include <bits/stdc++.h>

using namespace std;

const int N = 5e5+10; 
const int L = 100; 
double dp[N][L];
int pa[N];
// the key is note length at most L, since P(>=L) -> 0
// dp[.][i] := P(<i)
// reletion dp[u][i] = prod_v (0.5 + 0.5*dp[v][i-1])
// expectation simply formual E = sum_{i>0} (P>=i)
void solve() {
    cout << fixed << setprecision(10);
    int q; cin >> q;
    fill(dp[1]+1, dp[1]+L, 1);
    int n = 1;
    while (q--) {
        int op,x;
        cin >> op >> x;
        if (op == 1) {
            n++;
            fill(dp[n]+1, dp[n]+L, 1);
            pa[n] = x;
            double old = 1;
            for (int i = 1, y = n; i < L && x; i++) {
                double oold = dp[x][i];
                dp[x][i] /= 0.5 + 0.5*old;
                dp[x][i] *= 0.5 + 0.5*dp[y][i-1];
                old = oold;
                y = x; x = pa[x];
            }
        } else {
            double sum = 0;
            for (int i = 1; i < L; i++) {
                sum += dp[x][i];
            }
            sum = L-1 - sum;
            cout << sum << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
