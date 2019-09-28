#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n, D;
    cin >> n >> D;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }

    vector<int> dist(n);
    dist[0] = D;
    for (int i = 1; i < n; i++) {
        if (dist[i-1] > a[i-1]/2) {
            dist[i] = abs(dist[i-1] - a[i-1]);
        } else dist[i] = dist[i-1];
    }
    vector<ll> lim(n);
    lim[n-1] = 1;
    for (int i = n-1; i >= 1; i--) {
        if (lim[i] <= a[i]/2) lim[i-1]=lim[i];
        else lim[i-1] = lim[i] + a[i];
    }

    int q; cin >> q;
    while (q--) {
        int i; cin >> i; i--;
        cout << (lim[i]<=dist[i]? "YES\n": "NO\n");
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
