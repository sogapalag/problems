#include <bits/stdc++.h>

using namespace std;

const int N = 30; // bound, editiorial has lower bound
const int P = 30*10; 
bool dp[2][P][11];

void solve() {
    vector<int> a(10);
    int large = 0, id = -1;
    for (int i = 1; i <= 9; i++) {
        cin >> a[i];
        if (a[i] >= N) large++, id = i;
    }
    // feasible to cover 11.
    if (large >= 2) {
        cout << "YES"; return;
    }
    // > sum part calceled, otherwise sum(+-) > 1
    if (large == 1) {
        int sum = 0;
        for (int i = 1; i <= 9; i++) {
            if (i!=id) sum += a[i];
        }
        sum += 4;
        if ((sum&1) != (a[id]&1))sum++;
        a[id] = min(a[id], sum);
    }
    memset(dp, 0, sizeof dp);
    dp[0][0][0] = 1;
    int crt = 0;
    int lim = P-2;
    for (int i = 1; i <= 9; i++) {
        for (int _ = 0; _ < a[i]; _++) {
            int nxt = crt^1; 
            memset(dp[nxt], 0, sizeof dp[nxt]);
            for (int j = 0; j < lim; j++) {
                for (int k = 0; k < 11; k++) {
                    dp[nxt][j+1][(k+i)%11] |= dp[crt][j][k];
                    dp[nxt][j][(k-i+11)%11] |= dp[crt][j][k];
                }
            }
            crt ^= 1;
        }
    }
    int sum = 0;
    for (int i = 1; i <= 9; i++) {
        sum += a[i];
    }
    bool res = dp[crt][sum/2][0];
    cout << (res?"YES":"NO");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
        cout << "\n";
    }
    fflush(stdout);
}
