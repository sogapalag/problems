#include <bits/stdc++.h>

using namespace std;


void solve() {
    string s; cin >> s;
    int n = s.size();
    for (int i = 1; i < n; i++) {
        if (s[i-1]==s[i]) {
            cout << i << ' ' << (i+1); return;
        }
    }
    for (int i = 2; i < n; i++) {
        if (s[i-2] == s[i]) {
            cout << (i-1) << ' ' << (i+1); return;
        }
    }
    cout << "-1 -1";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
