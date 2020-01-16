#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int x,y;
    cin >> x >> y;
    int cnt = 0;
    for (int i = 1; i <= 9; i++) {
        int n = pow(10,i)-1;
        if (n <= y)cnt++;
    }
    cout << (1ll*x*cnt) << '\n';
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
