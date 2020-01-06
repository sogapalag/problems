#include <bits/stdc++.h>

using namespace std;


// a direct formula, O(n 2^n)
// dp[msk]: E (msk -> MSK-1)
void __solve() {
    int n; cin >> n;
    double sum = 0;
    vector<double> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    for (auto& x: a) {
        x /= sum;
    }
    const int MSK = 1<<n; 
    vector<double> dp(MSK);
    dp[MSK-1] = 0;
    for (int msk = MSK-2; msk >= 0; msk--) {
        double prob = 0;
        for (int i = 0; i < n; i++) {
            if (msk>>i&1) prob += a[i];
        }
        double E = 1;
        for (int i = 0; i < n; i++) {
            if (msk>>i&1) continue;
            E += a[i] * dp[msk|1<<i];
        }
        dp[msk] = E / (1-prob);
    }
    cout << fixed << setprecision(10) << dp[0];
}

// tag: coupon collector problem
// a simplified version of agc038e. O(sum A)
void solve() {
    int n; cin >> n;
    const int N = 2048; 
    vector<double> dp(N);
    dp[0] = -1;
    int sum = 0;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        for (int i = sum; i >= 0; i--) {
            dp[i+x] -= dp[i];
        }
        sum += x;
    }
    double res = 0;
    for (int i = 1; i <= sum; i++) {
        res += dp[i] / i;
    }
    res *= sum;
    cout << fixed << setprecision(10) << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
