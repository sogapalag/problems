#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n; cin >> n;
    ll a=0, b=0;
    for (int _ = 0; _ < n; _++) {
        ll x; cin >> x;
        a += x;
        b ^= x;
    }
    cout << "2\n";
    cout << b << ' ';
    a += b; b = 0;
    cout << a << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
