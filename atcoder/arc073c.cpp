#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n, T;
    cin >> n >> T;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }

    ll sum = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] > a[i-1]+T) sum += T;
        else sum += a[i]-a[i-1];
    }
    sum += T;
    cout << sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
