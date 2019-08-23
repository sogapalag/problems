#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    int z = -1;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] < 0) z = i;
    }
    int mi = 1e9;
    if (z-k+1 >= 0) mi = min(mi, -a[z-k+1]);
    if (z+k < n) mi = min(mi, a[z+k]);
    for (int i = 1; i < k; i++) {
        int l = z+i-k+1, r = z+i;
        if (0 <= l && r < n) {
            mi = min(mi, a[r]*2 - a[l]);
            mi = min(mi, a[r] - 2*a[l]);
        }
    }
    cout << mi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
