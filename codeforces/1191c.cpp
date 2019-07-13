#include <bits/stdc++.h>

using namespace std;

using ll=long long ;
void solve() {
    ll n, m, k;
    cin >> n >> m >> k;
    vector<ll> a(m);
    for (auto& x: a) {
        cin >> x;
        x--;
    }
    int res = 0;
    int i = 0;
    while (i < m) {
        ll pos = (a[i] - i) % k;
        int j = i+1;
        while (j < m && a[j] - a[i] <= k-1 - pos) {
            j++;
        }
        res++;
        i = j;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
