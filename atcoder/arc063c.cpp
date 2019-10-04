#include <bits/stdc++.h>

using namespace std;


void solve() {
    string s; cin >> s;
    int n = s.size();
    int cnt = 0;
    for (int i = 1; i < n; i++) {
        if (s[i] != s[i-1]) cnt++;
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
