#include <bits/stdc++.h>

using namespace std;


// must be [a_i, a_{i+k}] 's middle.
void solve() {
    int t; cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        int x = -1, mi = 1<<30;
        vector<int> a(n);
        for (auto& x: a) {
            cin >> x;
        }
        for (int i = 0; i+k < n; i++) {
            int tx = (a[i] + a[i+k]) / 2;
            int tmp = (a[i+k] - a[i] + 1)/2;
            if (tmp < mi) {
                x = tx;
                mi = tmp;
            }
        }
        cout << x << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
