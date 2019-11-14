#include <bits/stdc++.h>

using namespace std;


// some x occur 2 is sufficient
// min form [x...x], note yy coverd <[xyyx], so just min
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    vector<int> pre(n+1, -1);
    int mi = 10*n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (pre[x] != -1) {
            mi = min(mi, i - pre[x] + 1);
        }
        pre[x] = i;
    }
    if (mi > n) mi = -1;
    cout << mi << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
