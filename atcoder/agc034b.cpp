#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    string s; cin >> s;
    int n = s.size();
    string t;
    for (int i = 0; i < n; i++) {
        if (s[i]=='A') t += 'A';
        else if (s[i] == 'C') t += '#';
        else {
            if (i+1 < n && s[i+1] == 'C') {
                t += 'D'; i++;
            } else {
                t += '#';
            }
        }
    }
    n = t.size();

    ll res = 0;
    int ant = 0;
    for (char c: t) {
        if (c == '#') ant = 0;
        else if (c == 'A') ant++;
        else if (c == 'D') res += ant;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
