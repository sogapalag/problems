#include <bits/stdc++.h>

using namespace std;

const int P = 998244353; 

// left-upper, 4, other left/upper, 2, so 2^{n+m} since remain, each 2x2 dicided.
void solve() {
    int n,m;
    cin >> n >> m;
    int res = 1;
    for (int _ = 0; _ < n+m; _++) {
        res *= 2;
        res %= P;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
