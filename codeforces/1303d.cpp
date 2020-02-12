#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    ll d; int n;
    cin >> d >> n;
    vector<ll> a(64);
    ll sum = 0;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        sum += x;
        a[__builtin_ctz(x)]++;
    }
    if (sum < d) {
        cout << "-1\n";return;
    }

    ll res = 0;
    for (int i = 0; i < 63; i++) {
        if (d>>i&1) {
            if (a[i] > 0) a[i]--;
            else {
                int j;
                for (j = i+1; j < 63; j++) {
                    if (a[j] > 0) break;
                }
                res += j-i;
                a[j]--;
                for (int k = i; k < j; k++) {
                    a[k]++;
                }
            }
        }
        a[i+1] += a[i]/2;
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
