#include <bits/stdc++.h>

using namespace std;


// floor all, repair those can
void solve() {
    int n; cin >> n;
    vector<double> a(n);
    vector<long long> b(n);
    long long sub = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = floor(a[i]);
        sub += b[i];
    }
    int k = 0 - sub;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (cnt < k && a[i] != b[i]) {
            b[i]++; cnt++;
        }
        if (cnt == k) break;
    }
    for (auto& x: b) {
        cout << x << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
