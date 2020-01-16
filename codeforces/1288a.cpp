#include <bits/stdc++.h>

using namespace std;
const int SQ = 4e4; 

void solve() {
    int n,d;
    cin >> n >> d;
    for (int i = 0; i < min(n, SQ); i++) {
        int x = i + (d+i)/(i+1);
        if (x <= n) {
            cout << "YES\n";return;
        }
    }
    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
