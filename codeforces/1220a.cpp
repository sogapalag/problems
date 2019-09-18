#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    string s; cin >> s;
    int x = 0, y = 0;
    for (char c : s) {
        if (c == 'r') x++;
        if (c == 'n') y++;
    }
    for (int _ = 0; _ < y; _++) {
        cout << "1 ";
    }
    for (int _ = 0; _ < x; _++) {
        cout << "0 ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
