#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,m;
    cin >> n >> m;
    int sq = 1;
    while (sq*sq < n) sq++;
    vector<vector<int>> g(n);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    vector<int> pa(n, -1), d(n, -1);
    function<void(int,int,int)> dfs = [&](int u, int p, int depth){
        pa[u] = p;
        d[u] = depth;
        for (int v:g[u])if(v!=p){
            if (d[v] == -1) dfs(v,u,depth+1);
            else if (d[u]-d[v]+1 >= sq){
                cout << "2\n";
                cout << d[u]-d[v]+1 << "\n";
                int x = u;
                while (x != v) {
                    cout << x+1 << ' '; // 1-based
                    x = pa[x];
                }
                cout << x+1;
                exit(0);
            }
        }
    };
    dfs(0,-1,0);

    // there are many solution
    // below is easy to impl. by depth mod.
    // since same depth won't connect, and by mod, by no cycle>=sq, i.e. no back-edge connect them.
    vector<vector<int>> group(sq);
    for (int i = 0; i < n; i++) {
        group[d[i] % (sq-1)].push_back(i);
    }
    for (auto& a: group) {
        if (a.size() >= sq) {
            cout << "1\n";
            for (int i = 0; i < sq; i++) {
                cout << a[i]+1 << ' '; // 1-based
            }
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
