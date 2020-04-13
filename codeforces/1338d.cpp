#include <bits/stdc++.h>

using namespace std;


// 1. blues form indep set
// 2. all reds must on a path. (cause red adj continous(in nested sense) blues)
//    note the red does't adj any blue aren't necessary on path(treat black)
void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vector<int> blue(n), red(n);
    int res = 0;
    function<void(int,int)> dfs = [&](int u,int p){
        int b[2] = {};
        int r[2] = {};
        int cnt = 0;
        for (int v:g[u])if(v!=p){
            dfs(v,u);
            ++cnt;
            int x = red[v];
            if (b[1] < x) b[1] = x;
            if (b[0] < b[1]) swap(b[0], b[1]);
            int y = max(blue[v], x);
            if (r[1] < y) r[1] = y;
            if (r[0] < r[1]) swap(r[0], r[1]);
        }
        res = max(res, b[0]+b[1]+1);
        blue[u] = b[0]+1;
        res = max(res, cnt-2 + r[0]+r[1] + (p!=-1)); // p as blue case needed.
        red[u] = max(0, r[0] + cnt-1);
        res = max(res, red[u]);
    };
    dfs(0,-1);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
