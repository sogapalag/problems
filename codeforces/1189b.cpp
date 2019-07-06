#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    if (a[n-3] + a[n-2] <= a[n-1]) {
        cout << "NO"; return;
    }
    cout << "YES" << "\n";
    int i = 0;
    while (i < n) {
        cout << a[i] << ' ';
        i += 2;
    }
    i--;
    if (i >= n) i -= 2;
    while (i > 0) {
        cout << a[i] << ' ';
        i -= 2;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
