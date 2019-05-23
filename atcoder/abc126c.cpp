#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, k;
    cin >> n >> k;
    long double res = 0.0;
    for (int i = 1; i <= n; i++) {
        long double p = 1.0;
        int j = i;
        while (j<k) {
            j <<= 1;
            p /= 2;
        }
        res += p;
    }
    res /= n;
    cout << fixed << setprecision(12) << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
