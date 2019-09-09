#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,m;
    cin >> n >> m;
    long long res;
    if (n>m) swap(n,m);
    if (n == 1) {
        if (m == 1) res = 1;
        else res = m-2;
    } else {
        res = 1ll*(n-2) * (m-2);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
