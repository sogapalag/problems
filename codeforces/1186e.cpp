#include <bits/stdc++.h>

using namespace std;

using ll=long long;

const int N = 1003; 
int d[N][N];
int sum[2][N][N];

// 0 1 10 1001 ... bits ones pattern.
void solve() {
    memset(d, 0, sizeof d);
    memset(sum, 0, sizeof sum);
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c; cin >> c;
            d[i][j] = (c=='1');
        }
    }
    for (int i = 1; i <= n; i++) {
        int tmp = 0;
        for (int j = 1; j <= m; j++) {
            tmp += d[i][j];
            sum[0][i][j] = sum[0][i-1][j] + tmp;
            //cout << sum[0][i][j] << "\n";
            sum[1][i][j] = i*j - sum[0][i][j];
        }
    }

#define ones(x) __builtin_popcount(x)

    auto f = [&](int x, int y){
        if (!x || !y) return 0ll;
        int u = x/n, v = y/m;
        ll res = 1ll*((ll)u*v/2)* n*m;

        int b = (ones(u-1)+ones(v-1)) & 1;
        if (((ll)u*v)&1) res += sum[b][n][m];

        res += 1ll*(u/2)* n*(y%m) + 1ll*(v/2)* m*(x%n);

        b = (ones(u-1) + ones(v))&1;
        if (u&1)
            res += sum[b][n][y%m];
        b = (ones(u) + ones(v-1))&1;
        if (v&1)
            res += sum[b][x%n][m];
        b = (ones(u)+ones(v))&1;
        res += sum[b][x%n][y%m];
        return res;
    };

    auto qry = [&](int x, int y, int i, int j){
        return f(i, j) - f(x-1, j) - f(i, y-1) + f(x-1, y-1);
    };
    while (q--) {
        int x, y, i, j;
        cin >> x >> y >> i >> j;
        cout << qry(x, y, i, j) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
