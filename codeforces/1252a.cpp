#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        cout << (n+1 - x) << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
