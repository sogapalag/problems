#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// we can achieve any in [L,H], so shrink k in this
void solve() {
    ll n, k;
    cin >> n >> k;
    const ll L = (n+1)*n/2;
    const ll H = (n/2 + 1 + n)* ((n+1)/2) - (n%2==0?0:(n+1)/2);
    if (k < L) {
        cout << -1; return;
    }
    if (k >= H) { // 5 4 3 2 1
        cout << H << "\n";
        for (int i = 1; i <= n; i++) {
            cout << i << ' '; 
        }
        cout << "\n";
        for (int i = n; i >= 1; i--) {
            cout << i << ' ';
        }
        return;
    }

    // each step swap l,r get max diff
    // 5 ... 1
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);
    int l = 0, r = n-1;
    ll d = k - L;
    while (d > 0) {
        if (d >= a[r]-a[l]) {
            d -= a[r]-a[l];
            swap(a[r],a[l]);
            l++; r--;
        } else {
            swap(a[l], a[l+d]); break;
        }
    }
    cout << k << "\n";
    for (int i = 1; i <= n; i++) {
        cout << i << ' ';
    }
    cout << "\n";
    for (auto& x: a) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
