#include <bits/stdc++.h>

using namespace std;


void solve() {
    int h, n;
    cin >> h >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    int cost = 0;
    for (int i = 1; i < n; i++) {
        int x = a[i];
        if (h - x > 1) h = x + 1;
        if (i+1 < n && h - a[i+1] == 2) {
            h = a[i+1]; i++; continue;
        }
        if (i+1 == n && h <= 2) {
            h = 0; i++; continue;
        }
        cost++; h = x;
    }
    cout << cost << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
