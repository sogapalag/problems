#include <bits/stdc++.h>

using namespace std;


void solve() {
    string s;
    cin >> s;
    bool t = false;
    for (int i = 0; i < 3; i++) {
        t |= s[i] == s[i+1];
    }
    cout << (t?"Bad":"Good");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
