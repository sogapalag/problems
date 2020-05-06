#include <bits/stdc++.h>

using namespace std;


// it's optimal take best len=k
// since any len=k achievable, [x ( x| )  ], by reserve same space x=x one side, as long as watered, we paited that side too.
void solve() {
    int n; cin >> n;
    string s; cin >> s;
    vector<int> sum(n + 1);
    for (int i = 0; i < n; i++) {
        sum[i+1] = sum[i] + (s[i]-'0');
    }
    int res = 0;
    int k = (n+1)/2;
    for (int i = k; i <= n; i++) {
        res = max(res, sum[i] - sum[i-k]);
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
