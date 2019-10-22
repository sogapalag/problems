#include <bits/stdc++.h>

using namespace std;

using ll=long long;

void solve() {
    string s; cin >> s;
    ll K; cin >> K;
    ll cnt = 0;
    int n = s.size();
    bool all_same = true;
    for (int i = 1; i < n; i++) {
        all_same &= s[i] == s[0];
        if (s[i] != s[i-1]) continue;
        cnt++; i++;
    }
    if (all_same) {
        ll res = (n*K)/2;
        cout << res; return;
    }
    ll res = cnt*K;
    if (s[0] == s[n-1]) {
        int a = 0, b = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] != s[0]) break;
            a++;
        }
        for (int i = n-1; i >= 0; i--) {
            if (s[i] != s[n-1]) break;
            b++;
        }
        // the K-1 connections need addtional when a,b both odd
        if ((a&1) && (b&1)) res += K-1;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
