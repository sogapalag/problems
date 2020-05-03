#include <bits/stdc++.h>

using namespace std;


void solve() {
    int x,y; string s;
    cin >> x >> y >> s;
    int res = 1e9;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        if (s[i]=='E')x++;
        if (s[i]=='W')x--;
        if (s[i]=='N')y++;
        if (s[i]=='S')y--;
        int t = abs(x)+abs(y);
        if (t <= i+1) {
            res = min(res, i+1);
        }
    }
    if (res > 1e8) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << res << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
