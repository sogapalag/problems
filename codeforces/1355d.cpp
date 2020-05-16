#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,s;
    cin >> n >> s;
    if (n+n-1 < s) {
        cout << "YES\n";
        for (int i = 1; i < n; i++) {
            cout << "1 ";
        }
        cout << (s-n+1) << '\n';
        cout << n;
    } else {
        cout << "NO";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
