#include <bits/stdc++.h>

using namespace std;

using ll=long long;
void solve() {
    ll x,y;
    cin >> x >> y;
    auto res = x-y >= 2 ? "YES\n":"NO\n";
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
