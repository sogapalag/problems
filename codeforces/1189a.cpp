#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    string s; cin >> s;
    int a = 0, b = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') a++;
        else b++;
    }
    if (a != b) {
        cout << 1 << "\n";
        cout << s;
    } else {
        cout << 2 << "\n";
        s.push_back(' '); swap(s[n-1], s[n]);
        cout << s;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
