#include <bits/stdc++.h>

using namespace std;

using ll=long long ;

void solve() {
    ll n, k;
    cin >> n >> k;
    for (ll i = 1; i <= min(n, (ll)500000); i++) {
        ll j = n - i;
        if (i*(i+1)/2 - j == k) {
            cout << j; return;
        }
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
