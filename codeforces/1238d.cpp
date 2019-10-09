#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// only x##..#  , xx..x# invalid
void solve() {
    int n; cin >> n;
    string s; cin >> s;
    int len = 1;
    ll sum = 0;
    for (int i = 1; i < n; i++) {
        if (s[i] == s[i-1]) {
            len++;
        } else {
            sum += len;
            len = 1;
        }
    }
    //cout << sum << "\n";
    reverse(s.begin(), s.end());
    len = 1;
    int rep = 0;
    for (int i = 1; i < n; i++) {
        if (s[i] == s[i-1]) {
            len++;
        } else {
            sum += len;
            len = 1;
            rep++;
        }
    }
    //cout << sum << "\n";
    //cout << rep << "\n";
    sum -= rep;
    ll res = 1ll*n*(n-1)/2 - sum;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
