#include <bits/stdc++.h>

using namespace std;

int dx[4] = {1,0,-1,0 };
int dy[4] = {0,1, 0,-1};

int c[111][111];

void solve() {
    int n,m;
    cin >> n >> m;
    int k; cin >> k;
    vector<int> a(k);
    for (auto& x: a) {
        cin >> x;
    }
    memset(c, -1, sizeof c);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            c[i][j] = 0;
        }
    }
    int d = 0;
    function<pair<int, int> (int,int)> nxt = [&](int i, int j)->pair<int,int>{
        int x = i + dx[d];
        int y = j + dy[d];
        if (c[x][y]) {
            d = (d+1)%4;
            return nxt(i, j);
        }
        return {x,y};
    };
    int i=0, j=1;
    for (int t = 0; t < k; t++) {
        for (int _ = 0; _ < a[t]; _++) {
            tie(i,j) = nxt(i,j);
            c[i][j] = t+1;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << c[i][j] << ' ';
        }cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
