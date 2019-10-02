#include <bits/stdc++.h>

using namespace std;

using ll=long long;

int n;
vector<int> a;

// https://rogerdtz.github.io/2018/10/18/arc066e_Addition%20and%20Subtraction%20Hard/
ll calc() {
    ll dp[3]; // till now #(open)bra
    dp[1] = dp[2] = -(1ll<<60);
    dp[0] = 0;
    for (int x: a) {
        dp[0] += x;
        dp[1] -= x;
        dp[2] += x;
        if (x < 0) {// new bra
            dp[2] = max(dp[2], dp[1]);
            dp[1] = max(dp[1], dp[0]);
        }
        // new ket
        dp[0] = max(dp[0], dp[1]);
        dp[1] = max(dp[1], dp[2]);
    }
    return dp[0];
}
// greedy
// if draw braket, must be the form -((a_i+..+) - (..+..).. - (..+..) )
// aka, cost till next neg, those pos (+ -> -).
//      profit, all behind neg (- -> +).
ll calc2() {
    ll base = 0;
    ll pos = 0;
    ll neg = 0;
    ll mx = 0;
    for (int i = n-1; i >= 0; i--) {
        int x = a[i];
        base += x;
        if (x < 0) {
            mx = max(mx, (-neg-pos)*2);
            pos = 0;
            neg += x;
        } else pos += x;
    }
    return base + mx;
}

void solve() {
    cin >> n; a.resize(n);
    for (int i = 0; i < n; i++) {
        char c = '+';
        if (i) cin >> c;
        cin >> a[i];
        if (c=='-') a[i]*=-1;
    }
    ll x = calc();
    ll y = calc2();
    assert(x == y);
    cout << y << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
