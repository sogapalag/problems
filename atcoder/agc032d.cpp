#include <bits/stdc++.h>

using namespace std;


// first note rotate <=> insert after(cost A), or before (cost B)
//     and there is at aleast one no need to move.
// then view dp[i] as, a[i] not move, cost make a[0~i-1] to operation surround it.
// careful, dp[i] not solution 0~i. since it require at aleast a[i] not move.
// but we append n+1. since dp[n+1] will iter dp[0~n], aka, the solution.
void solve() {
    int n, A, B;
    cin >> n >> A >> B;
    vector<int> a(n+2);
    a[0] = 0; a[n+1] = n+1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<long long> dp(n+2, 1ll<<60);
    dp[0] = 0;
    for (int i = 1; i <= n+1; i++) {
        int cnt = 0;
        for (int j = i-1; j >= 0; j--) {
            if (a[j] < a[i]) {// here compare ensure sortness
                dp[i] = min(dp[i], dp[j] + 1ll*cnt*A + 1ll*(i-1-j-cnt)*B);
            } else {
                cnt++;
            }
        }
    }
    cout << dp[n+1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
