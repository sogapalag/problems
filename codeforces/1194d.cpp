#include <bits/stdc++.h>

using namespace std;


// k%3 = 1,2. LWWLWWLWW... same as original step only 1,2 game
// k%3 = 0.  (LWWLWW..LWW) W (LWWLWW..LWW) W (..) W ()
//  () size=k, i.e. period k+1.
void solve() {
    int n, k;
    cin >> n >> k;
    bool res;
    if (k%3 > 0) {
        res = n%3 != 0;
    } else {
        n %= (k+1);
        if (n == k) res = 1;
        else res = n%3 != 0;
    }
    cout << (res?"Alice":"Bob") << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
