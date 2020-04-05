#include <bits/stdc++.h>

using namespace std;


void solve() {
    string s; cin >> s;
    int n = s.size();
    auto S = s;
    vector<int> a(n+1), b(n+1);
    for (char x = '9'; x > '0'; x--) {
        for (int i = 0; i < n;) {
            if (s[i]==x) {
                int j = i;
                while (j < n && s[j]==x) {
                    --s[j];
                    j++;
                }
                a[i]++; b[j]++;
                i = j;
            } else i++;
        }
    }
    for (int i = 0; i < n; i++) {
        while (b[i]--) {
            cout << ')';
        }
        while (a[i]--) {
            cout << '(';
        }
        cout << S[i];
    }
    while (b[n]--) {
        cout << ')';
    }
    cout << '\n';
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
