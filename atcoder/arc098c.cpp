#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    string s; cin >> s;
    vector<int> pre(n+1), suf(n+1);
    pre[0] = 0;
    for (int i = 1; i <= n; i++) {
        pre[i] += pre[i-1] + (s[i-1]=='W');
    }
    suf[n] = 0;
    for (int i = n-1; i >= 0; i--) {
        suf[i] += suf[i+1] + (s[i]=='E');
    }
    int res = n;
    for (int i = 0; i < n; i++) {
        int tmp = pre[i] + suf[i+1];
        res = min(res, tmp);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
