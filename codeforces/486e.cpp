#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<int> len(n);
    {
        vector<int> dp(n+1, 1e9);
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            int x = a[i];
            int k = lower_bound(dp.begin(), dp.end(), x) - dp.begin();
            len[i] = k;
            dp[k] = x; // knuth, replace should-pos to x.
        }
    }
    vector<int> len2(n);
    {
        vector<int> dp(n+1, 0);
        dp[n] = 1e9;
        for (int i = n-1; i >= 0; i--) {
            int x = a[i];
            int k = upper_bound(dp.begin(), dp.end(), x) - dp.begin();
            k--;
            len2[i] = n-k;
            dp[k] = x;
        }
    }
    // https://codeforces.com/blog/entry/14678?#comment-196550
    // key: note if i in every(3), => len[i] is unique, i.e. every LIS pass it at such-len.
    vector<int> res(n, 1);
    vector<int> cnt(n+1, 0);
    int m = *max_element(len.begin(), len.end());
    for (int i = 0; i < n; i++) {
        if (len[i] + len2[i] - 1 == m) {
            cnt[len[i]]++;
            res[i] = 2;
        }
    }
    for (int i = 0; i < n; i++) {
        if (res[i] == 2 && cnt[len[i]] == 1) res[i] = 3;
    }
    for (auto& x: res) {
        cout << x;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
