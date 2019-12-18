#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    ll n; cin >> n;
    if (n > 14) {
        ll x = n%14;
        if (0<x && x<7) {
            cout << "YES\n"; return;
        }
    }
    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
