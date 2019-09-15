#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    string s; cin >> s;
    int x = 0, y = 0;
    int a = 0, b = 0;
    for (int i = 0; i < (n/2); i++) {
        if (s[i]=='?') a++;
        else {
            x += s[i]-'0';
        }
    }
    for (int i = n/2; i < n; i++) {
        if (s[i]=='?') b++;
        else {
            y += s[i]-'0';
        }
    }
    // make one-side more
    if (x + (a+1)/2 * 9 != y + (b+1)/2 * 9) {
        cout << "Monocarp"; return;
    }
    cout << "Bicarp";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
