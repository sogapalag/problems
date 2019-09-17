#include <bits/stdc++.h>

using namespace std;

using ll=long long ;

void solve() {
    ll n; cin >> n;
    for (int i = 1; i <= 3500; i++) {
        for (int j = 1; j <= 3500; j++) {
            ll p = n*i*j;
            ll q = 4*i*j - n*(i+j);
            if (q > 0 && p%q==0) {
                ll k = p/q;
                cout << i << ' ' << j << ' ' << k;
                return;
            }
        }
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
