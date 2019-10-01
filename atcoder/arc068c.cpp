#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    ll x; cin >> x;
    ll res = x/11 * 2;
    x%=11;
    res += (x>0) + (x>6);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
