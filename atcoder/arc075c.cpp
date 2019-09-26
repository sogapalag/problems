#include <bits/stdc++.h>

using namespace std;

using Bs = bitset<10010>;

void solve() {
    int n; cin >> n;
    Bs b; b[0] = 1;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        b |= b<<x;
    }
    int res = 0;
    for (int i = 0; i <= 10000; i++) {
        if (i%10==0 || !b[i]) continue;
        res = max(res, i);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
