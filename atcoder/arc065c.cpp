#include <bits/stdc++.h>

using namespace std;


void solve() {
    string s; cin >> s;
    reverse(s.begin(), s.end());
    vector<string> pre = {"dream", "dreamer", "erase", "eraser"};
    for (auto& x: pre) {
        reverse(x.begin(), x.end());
    }
    int i = 0, n = s.size();
    while (i < n) {
        if (s.substr(i, 5) == pre[0] || s.substr(i, 5) == pre[2])
            i += 5;
        else if (s.substr(i, 6) == pre[3])
            i += 6;
        else if (s.substr(i, 7) == pre[1])
            i += 7;
        else {
            cout << "NO"; return;
        }
    }
    cout << "YES";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
