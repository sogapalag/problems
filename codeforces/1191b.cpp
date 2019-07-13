#include <bits/stdc++.h>

using namespace std;


void solve() {
    int a[3][9];
    memset(a, 0, sizeof a);
    for (int i = 0; i < 3; i++) {
        string s; cin >> s;
        if (s[1] == 's') {
            a[0][s[0]-'1']++;
        } else if (s[1] == 'm') {
            a[1][s[0]-'1']++;
        } else if (s[1] == 'p') {
            a[2][s[0]-'1']++;
        }
    }
    int res = 2;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 9; j++) {
            res = min(res, 3-a[i][j]);
        }
        for (int j = 1; j+1 < 9; j++) {
            res = min(res, 3 - (a[i][j-1]>0) - (a[i][j]>0) - (a[i][j+1]>0));
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
