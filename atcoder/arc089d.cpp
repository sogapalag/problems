#include <bits/stdc++.h>

using namespace std;

#define rep(i) for(int i=0;i<2;i++)

const int K = 1024;
int sum[2][K<<1][K<<1];

void solve() {
    int n,k;
    cin >> n >> k;
    int m = k<<1;
    for (int _ = 0; _ < n; _++) {
        int x,y; char c;
        cin >> x >> y >> c;
        sum[c=='B'][x%m+1][y%m+1] += 1;
    }
    rep(c){
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= m; j++) {
                sum[c][i][j] += sum[c][i][j-1];
            }
            for (int j = 1; j <= m; j++) {
                sum[c][i][j] += sum[c][i-1][j];
            }
        }
    }
    auto q = [&](int c, int x,int y,int u,int v){
        return sum[c][u][v] - sum[c][x][v] - sum[c][u][y] + sum[c][x][y];
    };
    int res = 0;
    rep(c)
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            int w = 0;
            w += q(c, 0,0, k-i,k-j);
            w += q(c, m-i,0, m,k-j);
            w += q(c, 0,m-j, k-i,m);
            w += q(c, k-i,k-j, m-i,m-j);
            w += q(c, m-i,m-j, m,m);
            int b = 0;
            b += q(c^1, k-i,0, m-i,k-j);
            b += q(c^1, 0,k-j, k-i,m-j);
            b += q(c^1, m-i,k-j, m,m-j);
            b += q(c^1, k-i,m-j, m-i,m);
            res = max(res, w+b);
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
