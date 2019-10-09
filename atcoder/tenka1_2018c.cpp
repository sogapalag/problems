#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end(), greater<int>());

    if (n&1) {
        int k = n/2;
        ll sum = 0;
        for (int i = 0; i < k; i++) {
            sum += a[i]<<1;
        }
        for (int i = k; i < n; i++) {
            sum -= a[i]<<1;
        }
        sum += a[k] + a[k+1];
        
        ll sum2 = 0;
        for (int i = 0; i <= k; i++) {
            sum2 += a[i]<<1;
        }
        for (int i = k+1; i < n; i++) {
            sum2 -= a[i]<<1;
        }
        sum2 -= a[k-1] + a[k];
        cout << max(sum, sum2);
    } else {
        int k = n/2;
        ll sum = 0;
        for (int i = 0; i < k; i++) {
            sum += a[i]<<1;
        }
        for (int i = k; i < n; i++) {
            sum -= a[i]<<1;
        }
        sum -= a[k-1];
        sum += a[k];
        cout << sum;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
