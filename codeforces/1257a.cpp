#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, x, a, b;
    cin >> n >> x >> a >> b;
    if (a > b) swap(a, b);
    int y = a-1 + n-b;
    int res = (b-a) + min(y, x);
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
