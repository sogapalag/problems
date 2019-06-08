#include <bits/stdc++.h>

using namespace std;

// every board add
// make suffix sum added
// so pick k largest, except whole sum, since board cannot before a[0].
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    long long res = 0;
    for (auto& x: a) {
        cin >> x;
        res += x;
    }
    vector<long long> b(n-1);
    reverse(a.begin(), a.end());
    b[0] = a[0];
    for (int i = 1; i < n-1; i++) {
        b[i] = b[i-1] + a[i];
    }
    sort(b.begin(), b.end(), greater<long long>());
    for (int i = 0; i < k-1; i++) {
        res += b[i];
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
