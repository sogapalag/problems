#include <bits/stdc++.h>

using namespace std;


void solve() {
    string s,t;
    cin >> s >> t;
    int n = s.size();
    vector<vector<int>> nxt(n+2, vector<int>(26, n+1));
    for (int i = n; i >= 0; i--) {
        for (int c = 0; c < 26; c++) {
            nxt[i][c] = nxt[i+1][c];
        }
        if (i<n) nxt[i][s[i]-'a'] = i+1;
    }
    int cnt = 0;
    int m = t.size();
    int j = 0;
    while (j < m) {
        int i = 0;
        int find = 0;
        while (j < m && i <= n) {
            if (nxt[i][t[j]-'a'] > n) break;
            find++;
            i = nxt[i][t[j]-'a'];
            j++;
        }
        if (!find) {
            cout << "-1\n"; return;
        }
        cnt++;
    }
    cout << cnt << '\n';
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
