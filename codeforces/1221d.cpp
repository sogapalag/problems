#include <bits/stdc++.h>

using namespace std;
using ll=long long ;
const long long INF = 0x3f3f3f3f3f3f3f3f;
#define rep(i) for(int i=0;i<3;i++)

const int N = 3e5+10; 
ll dp[N][3];//end with i, which +j time

void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    for (int i = 0; i < n; i++) {
        rep(j) dp[i][j] = INF;
    }
    rep(i) dp[0][i] = (ll)b[0]*i;
    for (int i = 1; i < n; i++) {
        rep(j)rep(k){
            if (a[i-1]+j == a[i]+k) continue;
            ll tmp = dp[i-1][j] + (ll)b[i]*k;
            dp[i][k] = min(dp[i][k], tmp);
        }
    }
    ll res = INF;
    rep(i) res = min(res, dp[n-1][i]);
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
