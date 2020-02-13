#include <bits/stdc++.h>

using namespace std;

const int N = 512; 
int a[5][N][N];
string T="RGYB";
// next time n~500, try O(n^3), don't think O(n^2) complicated
void solve() {
    int n,m,q;
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < 4; k++) {
                if (s[j]==T[k]) {
                    a[k][i+1][j+1] = 1;
                }
            }
        }
    }
    for (int _ = 0; _ < 4; _++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                a[_][i][j] += a[_][i-1][j] + a[_][i][j-1] - a[_][i-1][j-1];
            }
        }
    }
    auto sum  = [&](int i, int x,int y,int u,int v){
        return a[i][u][v] - a[i][x][v] - a[i][u][y] + a[i][x][y];
    };

    vector<tuple<int,int,int,int>> qrs(q);
    for (int i = 0; i < q; i++) {
        int x,y,u,v;
        cin >> x >> y >> u >> v;
        x--,y--;
        qrs[i] = {x,y,u,v};
    }
    vector<int> res(q);

    int lim = min(n/2, m/2);
    for (int r = 1; r <= lim; r++) {
        memset(a[4], 0, sizeof a[4]);
        for (int i = 0; i+2*r <= n; i++) {
            for (int j = 0; j+2*r <= m; j++) {
                if (sum(0, i,j, i+r, j+r) != r*r) continue;
                if (sum(1, i,j+r, i+r, j+2*r) != r*r) continue;
                if (sum(2, i+r,j, i+2*r, j+r) != r*r) continue;
                if (sum(3, i+r,j+r, i+2*r, j+2*r) != r*r) continue;
                a[4][i+1][j+1] = 1; // mark top-left
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                a[4][i][j] += a[4][i-1][j] + a[4][i][j-1] - a[4][i-1][j-1];
            }
        }
        for (int i = 0; i < q; i++) {
            int x,y,u,v;
            tie(x,y,u,v) = qrs[i];
            if (u-x >= 2*r && v-y >= 2*r) {
                // as long as top-left rect has mark;
                if (sum(4, x, y, u-2*r+1, v-2*r+1)) {
                    res[i] = r;
                }
            }
        }
    }
    for (auto& x: res) {
        cout << 4*x*x << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
