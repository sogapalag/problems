#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    int m = 1 + (n/2);
    cout << m << "\n";
    for (int i = 1; i <= n; i++) {
        int r = (i+1)/2;
        int c = 1 + i/2;
        cout << r << " " << c << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
