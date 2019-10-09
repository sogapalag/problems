#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, d;
    cin >> n >> d;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());

    n = a.size();
    reverse(a.begin(), a.end());
    for (int i = 1; i <= n; i++) {
        if (i >= n || a[i] <= 1ll*i*d) {
            cout << i << "\n"; return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
