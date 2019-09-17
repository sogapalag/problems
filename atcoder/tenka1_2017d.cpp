#include <bits/stdc++.h>

using namespace std;
using ll=long long ;

// y<K iff in some bit y_j=0, K_j=1, before that y=k
void solve() {
    int n, K;
    cin >> n >> K;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    K++; // now consider < K
    ll res = 0;
    int prefix = 0;
    // e.g.   K = 101 001..
    //   prefix = 100 0...0
    for (int j = 30; j >= 0; j--) {
        int k = 1<<j;
        if (K & k) {
            ll sum = 0;
            // get when x's bit <= prefix's bit
            for (int i = 0; i < n; i++) {
                int x = a[i];
                x -= x&(k-1); // discard j's right part
                if ((prefix | x) <= prefix) sum += b[i];
            }
            res = max(res, sum);
            prefix |= k;
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
