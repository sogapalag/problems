#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    bool t = (n <= m && n <= k);
    cout << (t?"Yes":"No");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
