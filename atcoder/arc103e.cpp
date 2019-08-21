#include <bits/stdc++.h>

using namespace std;


void solve() {
    string s; cin >> s;
    int n = s.size();
    bool ok = true;
    ok &= s[n-1] == '0';
    ok &= s[0] == '1';
    for (int i = 0; i < n-1; i++) {
        ok &= s[i] == s[n-i-2];
    }
    if (!ok) {
        cout << -1; return;
    }
    vector<pair<int, int>> res;
    int crt = 0;
    for (int i = 0; i < n; i++) {
        if (i < n-1 && s[i]=='0') continue;
        for (int j = crt; j < i; j++) {
            res.emplace_back(j, i);
        }
        crt = i;
    }
    for (auto& p: res) {
        int x,y;
        tie(x,y) = p;
        x++; y++;
        cout << x << ' ' << y << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
