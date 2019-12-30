#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n-1);
    for (auto& x: a) {
        cin >> x;
    }
    int root = a[0];
    int mx = n;
    vector<bool> trk(n+1);
    cout << root << "\n";
    for (int i = 0; i < n-1; i++) {
        int u = a[i];
        trk[u] = 1;
        while (trk[mx]) {
            mx--;
        }
        // consider a heavy chain root-mx. since 2^i, i.e. mx dominate.
        // explore order must visit this chian first.
        if (i+1<n-1 && !trk[a[i+1]]) {
            cout << u << ' ' << a[i+1] << "\n";
        } else {
            trk[mx] = 1;
            cout << u << ' ' << mx << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
