#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    int a,b,c;
    cin >> a >> b >> c;
    string s; cin >> s;
    string res(n, '#');
    int win = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'R' && b > 0) {
            res[i] = 'P'; b--; win++;
        }
        if (s[i] == 'P' && c > 0) {
            res[i] = 'S'; c--; win++;
        }
        if (s[i] == 'S' && a > 0) {
            res[i] = 'R'; a--; win++;
        }
    }
    // only care win
    //for (int i = 0; i < n; i++) {
    //    if (res[i] == '#') {
    //        if (s[i] == 'R') {
    //            if (a > 0) {
    //                res[i] = 'R'; a--;
    //            }else {
    //                assert(c > 0);
    //                res[i] = 'S'; c--;
    //            }
    //        } else if (s[i] == 'P') {
    //            if (b > 0) {
    //                res[i] = 'P'; b--;
    //            } else {
    //                assert(a > 0);

    //            }
    //        }
    //    }
    //}
    if (win < (n+1)/2) {
        cout << "NO\n"; return;
    }
    for (int i = 0; i < n; i++) {
        if (res[i] == '#') {
            if (a > 0) res[i] = 'R', a--;
            else if (b > 0) res[i] = 'P', b--;
            else res[i] = 'S', c--;
        }
    }
    cout << "YES\n";
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
