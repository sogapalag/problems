#include <bits/stdc++.h>

using namespace std;


void solve() {
    string s; cin >> s;
    int n = s.size();
    for (char x = 'a'; x <= 'z'; x++) {
        bool odd = false;
        int len = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == x) {
                len++;
            }else {
                if (len&1) {
                    odd = true; break;
                }
                len = 0;
            }
        }
        odd |= (len&1);
        if (odd) cout << x;
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
