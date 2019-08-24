#include <bits/stdc++.h>

using namespace std;

using ll=long long ;
void solve() {
    int n; ll m;
    cin >> n >> m;
    vector<ll> a(n+1);
    a[0] = 0;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        a[i] = a[i-1] + x;
        a[i] %= m;
    }
    map<ll, ll> cnt;
    for (ll x: a){
        cnt[x]++;
    }
    ll res = 0;
    for (auto& p: cnt) {
        ll t = p.second;
        res += t*(t-1)/2;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
