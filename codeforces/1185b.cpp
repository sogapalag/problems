#include <bits/stdc++.h>

using namespace std;


void solve() {
    string s, t;
    cin >> s;
    cin >> t;
    int i = 0, j = 0;
    int n = s.size(), m = t.size();
    while (i < n) {
        if (j >= m) {
            cout << "NO\n"; return;
        }
        if (s[i] != t[j]) {
            cout << "NO\n"; return; 
        }
        int cnt = 1;
        i++;
        while (i < n && s[i-1] == s[i]) {
            cnt++; i++;
        }
        int cnt2 = 1;
        j++;
        while (j < m && t[j-1] == t[j]) {
            cnt2++; j++;
        }
        if (cnt > cnt2) {
            cout << "NO\n"; return;
        }
    }
    if (j != m) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
    cout << endl;
}
