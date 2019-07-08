#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, a, b;
    cin >> n >> a >> b;
    int res = min(n*a, b);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
