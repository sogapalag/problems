#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vector<bool> mark(n);
    int root = -1;
    for (int _ = 0; _ < m; _++) {
        int x; cin >> x; x--;
        mark[x] = true;
        root = x;
    }
    function<void(int,int)> mark_between = [&](int u, int p){
        for (int v:g[u])if(v!=p){
            mark_between(v,u);
            mark[u] = mark[u] || mark[v];
        }
    };
    mark_between(root, -1);
    
    int res = -1, mx = -1;
    int e = 0;
    function<void(int,int,int)> dfs = [&](int u, int p, int depth){
        if (depth > mx || (depth == mx && u < res)) {
            mx = depth;
            res = u;
        }
        for (int v:g[u])if(v!=p && mark[v]){
            e++;
            dfs(v,u,depth+1);
        }
    };
    dfs(root, -1, 0);
    int E = e;
    root = res; res = -1; mx = -1; dfs(root, -1, 0);
    // one more dfs, is enough to get min-index
    root = res; dfs(root, -1, 0);
    //root = res; dfs(root, -1, 0);
    cout << res+1 << "\n";
    cout << 2*E - mx;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
