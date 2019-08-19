#include <bits/stdc++.h>

using namespace std;


// take u=s+t  mx = most consective a 
// then each round ....aaaa | aaaa..... double size
// rep of a = 2^(k-1) * mx
// note in final round aa..a in start
void solve() {
    int n, k;
    cin >> n >> k;
    string s; cin >> s;
    string t = s; reverse(t.begin(), t.end());
    string u = s + t;
    char mi = 'z';
    for (char x: s) {
        mi = min(mi, x);
    }
    int mx = 1;
    vector<int> len(2*n+1, 0);
    for (int i = 0; i < 2*n; i++) {
        len[i+1] = u[i] == mi ? len[i]+1 : 0;
        len[i+1] = min(len[i+1], n);
        mx = max(mx, len[i+1]);
    }
    if (k>15 || (1<<(k-1))*mx >= n) {
        for (int i = 0; i < n; i++) {
            cout << mi;
        }
        return;
    }
    int rep =(1<<(k-1)) * mx;
    int m = n - rep;
    string res = "{";
    for (int i = n+1; i <= 2*n; i++) {
        if (len[i] == mx) {
            string tmp = u.substr(i-m-mx, m);
            reverse(tmp.begin(), tmp.end());
            res = min(res, tmp);
        }
    }
    for (int i = 0; i < rep; i++) {
        cout << mi;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
