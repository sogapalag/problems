#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,k1,k2;
    cin >> n >> k1 >> k2;
    bool yes = false;
    for (int _ = 0; _ < k1; _++) {
        int x; cin >> x;
        yes |= (x==n);
    }
    for (int _ = 0; _ < k2; _++) {
        int x; cin >> x;
    }
    cout << (yes?"YES\n":"NO\n");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
