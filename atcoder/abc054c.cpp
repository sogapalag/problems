#include <bits/stdc++.h>

using namespace std;

int d[10][10];

void solve() {
    int n,m;
    cin >> n >> m;
    memset(d, 0, sizeof d);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        d[x][y] = d[y][x] = 1;
    }
    vector<int> perm(n);
    int cnt = 0;
    iota(perm.begin(), perm.end(), 0);
    do {
        if (perm[0]!=0) continue;
        bool y = true;
        for (int i = 1; i < n; i++) {
            y &= d[perm[i-1]][perm[i]];
        }
        if (y) cnt++;
    }while(next_permutation(perm.begin(), perm.end()));
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
