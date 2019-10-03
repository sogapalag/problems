#include <bits/stdc++.h>

using namespace std;

using ll=long long;
void solve() {
    int n, X;
    cin >> n >> X;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    ll res = 0;
    if (a[0] > X) {
        res += a[0]-X;
        a[0] = X;
    }
    for (int i = 1; i < n; i++) {
        if (a[i]+a[i-1] > X) {
            int d = a[i]+a[i-1]-X;
            res += d;
            a[i] -= d;
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
