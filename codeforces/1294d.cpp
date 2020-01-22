#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,m;
    cin >> n >> m;
    vector<bool> trk(n+1);
    vector<int> now(m);
    iota(now.begin(), now.end(), 0);
    int mex = 0;
    // [mex] inc. and <=n
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x; x%=m;
        int y = now[x];
        if (y < n) {
            trk[y] = true;
            now[x] += m; // greedy use next mod.
        }
        while (trk[mex]) {
            mex++;
        }
        cout << mex << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
