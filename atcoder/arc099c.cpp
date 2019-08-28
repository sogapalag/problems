#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
    }
    int res = (n-1+k-2)/(k-1);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
