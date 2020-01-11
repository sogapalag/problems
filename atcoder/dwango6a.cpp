#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<string> s(n);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        cin >> a[i];
    }
    string t; cin >> t;
    int sum = 0;
    for (int i = n-1; i >= 0; i--) {
        if (s[i] == t) {
            cout << sum; return;
        }
        sum += a[i];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
