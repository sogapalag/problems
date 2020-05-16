#include <bits/stdc++.h>

using namespace std;


// optimal is pick some prefix.
// and when which is decided, from largest, pick its near till.
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    sort(a.begin(), a.end());
    // some can stay in the camp. Russell is worried about this expedition
    //reverse(a.begin(), a.end());
    //int res = 0;
    //for (int i = 0;;) {
    //    ++res;
    //    i += a[i];
    //    if (i>=n) {
    //        res -= i>n;
    //        break;
    //    }
    //}
    //cout << res << "\n";

    vector<int> dp(n + 1);
    for (int i = 0; i < n; i++) {
        int k = i+1-a[i];
        if (k>=0) dp[i+1] = 1+dp[k];
    }
    int res = *max_element(dp.begin(), dp.end());
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
