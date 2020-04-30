#include <bits/stdc++.h>

using namespace std;
using ll=long long;
const ll INF = 0x3f3f3f3f3f3f3f3f;
// it's easy to use dp[len]:=min weight till now
// then key optim is len<=139,
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    int m = min(n, 139);
    vector<ll> dp(m + 1, INF);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        ll x = a[i];
        for (int j = m-1; j >= 0; j--)if(dp[j] <= 6*x){
            dp[j+1] = min(dp[j+1], dp[j] + x);
        }
    }
    int i;
    for (i = m; i >= 0; i--) {
        if (dp[i] < INF) break;
    }
    cout << i << '\n';
}

void test() {
    ll n = 0, sum = 0;
    ll end = 1;
    ll lim = 1e9;
    while (end < lim) {
        n++;
        sum += end;
        end = max(end, (sum+5)/6);
    }
    cerr<<n<<endl; // 139
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    if(0)test();
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
