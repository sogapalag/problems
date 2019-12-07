#include <bits/stdc++.h>

using namespace std;


// [a][b][c]..[x]..[c][b][a]
void solve() {
    string s; cin >> s;
    int n = s.size();
    int l = 0, r = n-1;
    while (true) {
        char c = s[l];
        if (s[l] != s[r]) {
            cout << 0; return;
        }
        int cnt = 1;
        while (l < r && s[l+1] == c) {
            l++;
            cnt++;
        }
        if (l == r) {
            if (cnt >= 2) {
                cout << cnt+1;
            } else {
                cout << 0;
            }return;
        }
        cnt++;
        while (s[r-1] == c) {
            r--;
            cnt++;
        }
        if (cnt < 3) {
            cout << 0; return;
        }
        l++; r--;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
