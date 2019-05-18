#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i] = abs(x);
    }
    sort(a.begin(), a.end());
    long long res = 0;
    for (int i = 0; i < n; i++) {
        int j = upper_bound(a.begin() + i + 1, a.end(), 2 * a[i]) - a.begin();
        res += j - i - 1;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
