#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    int k = 0;
    int x = 0, y = 0;
    for (int _ = 0; _ < n; _++) {
        string s; cin >> s;
        k += s.size()&1;
        for (char c: s) {
            if (c=='1')x++;
            else y++;
        }
    }
    x&=1; y&=1;
    int res = n;
    if (k == 0 && (x+y==2)) res--;
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
