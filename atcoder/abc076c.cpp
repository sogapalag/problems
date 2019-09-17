#include <bits/stdc++.h>

using namespace std;


void solve() {
    string s,t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    if (n < m) {
        cout << "UNRESTORABLE"; return;
    }
    set<string> res;
    for (int i = 0; i+m <= n; i++) {
        auto r = s;
        bool yes = true;
        for (int j = 0; j < m; j++) {
            if (r[i+j] == '?') {
                r[i+j] = t[j];
            }else if(r[i+j] != t[j]) {
                yes = false;
                break;
            }
        }
        if (yes) {
            for (int j = 0; j < n; j++) {
                if (r[j]=='?') r[j] = 'a';
            }
            res.insert(r);
        }
    }
    if (res.empty()) {
        cout << "UNRESTORABLE"; return;
    }
    cout << *res.begin();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
