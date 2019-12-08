#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<vector<pair<int,int>>> g(n);
    for (int i = 0; i < n; i++) {
        int m; cin >> m;
        for (int _ = 0; _ < m; _++) {
            int x, y;
            cin >> x >> y;
            x--;
            g[i].emplace_back(x,y);
        }
    }

    const int MSK = 1<<n; 
    int res = 0;
    for (int msk = 0; msk < MSK; msk++) {
        for (int i = 0; i < n; i++) {
            if (msk & (1<<i)) {
                for (auto& _: g[i]) {
                    int j, y;
                    tie(j, y) = _;
                    if (((msk>>j)&1) != y) goto end;
                }
            }
        }
        res = max(res, __builtin_popcount(msk));
end:;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
