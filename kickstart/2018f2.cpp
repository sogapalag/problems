#include <bits/stdc++.h>

using namespace std;

const int N = 55; 
int g[N][N];
// a naive construction, each step find min_edge S-(V/S), assign opposite. one can see this achieve LB.
// but this don't help much with counting.
// so we need the editorial construction process. note weights are distinct, could be zero
// d[u] = min_adj, f[u]= argmin_adj
// constructing process: by d[u] order(break tie with u) assign color
//  one can see when i is free? => f[i] undecided => d[f[i]]>=d[i], note d[f[i]]<=d[i] (f[i]-i edge)
//     => d[f[i]]==d[i] => f[f[i]]==i.
//     i.e. f[f[i]]==i && i<f[i]
//  and for special case weight be zero
//    any v!={x,y}, f[v]={x,y} is free too.
//     i.e. d[v]>0 && d[f[v]]==0
void solve() {
    memset(g, 0x3f, sizeof g);
    int n,m;
    cin >> n >> m;
    for (int _ = 0; _ < m; _++) {
        int x,y,z;
        cin >> x >> y >> z;
        --x;--y;
        g[x][y] = g[y][x] = z;
    }
    vector<int> d(n), f(n);
    for (int i = 0; i < n; i++) {
        f[i] = min_element(g[i], g[i]+n) - g[i];
        d[i] = g[i][f[i]];
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt += (f[f[i]]==i && f[i]>i) || (d[i]>0 && d[f[i]]==0);
    }
    cout << (1ll<<cnt) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
