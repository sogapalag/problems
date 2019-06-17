#include <bits/stdc++.h>

using namespace std;

using ll = long long ;
void solve() {
    ll x, y, z;
    cin >> x >> y >> z;
    ll sum = x/z + y/z;
    x %= z; y %= z;
    ll gi = 0;
    if (x+y >= z) {
        sum++;
        gi = min(z-x, z-y);
    }
    cout << sum << ' ' << gi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
