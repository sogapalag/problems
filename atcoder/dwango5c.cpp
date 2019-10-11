#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    int q; cin >> q;
    while (q--) {
        int k; cin >> k;
        ll d = 0, m = 0, dm = 0, dmc = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'D') d++;
            else if (s[i] == 'M') {
                m++;
                dm += d;
            } else if (s[i] == 'C') {
                dmc += dm;
            }

            if (i >= k-1) {
                if (s[i-k+1] == 'D') {
                    dm -= m;
                    d--;
                } else if (s[i-k+1] == 'M') {
                    m--;
                }
            }
        }
        cout << dmc << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
