#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,x;
    cin >> n >> x;
    string s; cin >> s;
    vector<int> a(n+1);
    for (int i = 0; i < n; i++) {
        a[i+1] = a[i] + (s[i]=='0' ? 1 : -1);
    }
    int t = a[n];
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (x==a[i]) {
            cnt++;
        } else {
            if (x > a[i] && t > 0) {
                if ((x-a[i])%t == 0) cnt++;
            }
            if (x < a[i] && t < 0) {
                if ((a[i]-x)%t == 0) cnt++;
            }
        }
    }
    if (cnt>0 && t==0) {
        cout << "-1\n";
    } else {
        cout << cnt << '\n';
    }
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
