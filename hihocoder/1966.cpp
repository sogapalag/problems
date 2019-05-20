#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    // compress
    vector<int> b(a);
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    map<int, int> map;
    for (int i = 0; i < b.size(); i++) {
        map[b[i]] = i+1;
    }
    for (auto& x: a) {
        x = map[x];
    }
    // prefix-max BIT
    // dp, [i][j], end with i,j. max-length
    vector<vector<int>> f(n+1, vector<int>(n+1, 0));
    for (int x: a) {
        vector<int> d(n+1);
        for (int j = 0; j <= n; j++) {
            int p = x;
            int tmp = 0;
            for (; p > 0; p -= (p&-p))
                tmp = max(tmp, f[p][j]);
            d[j] = 1 + max(f[0][j], tmp);
        }
        vector<int> c(n+1);
        for (int i = 0; i <= n; i++) {
            int p = x;
            int tmp = 0;
            for (; p > 0; p -= (p&-p))
                tmp = max(tmp, f[i][p]);
            c[i] = 1 + max(f[i][0], tmp);
        }
        // must after two query, then two upd.
        for (int j = 0; j <= n; j++) {
            int p = x;
            for (; p <= n; p += (p&-p))
                f[p][j] = max(f[p][j], d[j]);
        }
        for (int i = 0; i <= n; i++) {
            int p = x;
            for (; p <= n; p += (p&-p))
                f[i][p] = max(f[i][p], c[i]);
        }
    }
    int res = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            res = max(res, f[i][j]);
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
