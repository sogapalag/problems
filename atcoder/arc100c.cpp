#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] -= i+1;
    }
    sort(a.begin(), a.end());
    int b = a[n/2];
    long long res = 0;
    for (auto& x: a) {
        res += abs(x-b);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
