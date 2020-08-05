#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// #scc = #nodes - #edges
void solve() {
    int n; cin >> n;
    ll res = 0;
    for (int i = 0; i < n; i++) {
        res += (n-i) *1ll* (i+1);
    }
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        --x;--y;
        if (x > y) swap(x, y);
        res -= (x+1) *1ll* (n-y);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
