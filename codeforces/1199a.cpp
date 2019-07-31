#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    for (int i = 0; i < n; i++) {
        int l = max(0, i-x);
        int r = min(n-1, i+y);
        bool work = true;
        for (int j = l; j <= r; j++) {
            if (j==i) continue;
            if (a[j] <= a[i]) {
                work = false; break;
            }
        }
        if (work) {
            cout << i+1; return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
