#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,p;
    cin >> n >> p;
    for (int i = 1; i <= 31; i++) {
        int x = n-i*p;
        if (x >= i && __builtin_popcount(x) <= i) {
            cout << i; return;
        }
    }
    cout << -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
