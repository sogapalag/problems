#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,m,x;
    cin >> n >> m >> x;
    n = max(n,m);
    cout << (x+n-1)/n;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
