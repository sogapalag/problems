#include <bits/stdc++.h>

using namespace std;

int q(int x, int y){
    cout << "? " << x+1 << ' '<< y+1 << endl;
    int z; cin >> z;
    return z-1;
}

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
    vector<bool> trk(n);

    int mx = -1, rt = -1;
    vector<int> pa(n);
    function<void(int,int,int)> dfs = [&](int u, int p, int depth){
        if (depth > mx) {
            mx = depth;
            rt = u;
        }
        pa[u] = p;
        for (int v:g[u])if(v!=p&&!trk[v]){
            dfs(v,u,depth+1);
        }
    };
    auto get = [&](int u){
        mx = -1, rt = -1;
        dfs(u, -1, 0);
        return rt;
    };

    int u = 0;
    while (true) {
        // actually any two leaf is fine, below use diameter
        // since each time either find root, or cut out these two leaf. thus |q| <= n/2
        int x = get(u);
        int y = get(x);
        if (x == y) {
            u = x; break;
        }
        int z = q(x,y);
        if (z == x || z == y) {
            u = z; break;
        }
        dfs(z, -1, 0);
        {
            while (pa[x] != z) {
                x = pa[x];
            }
            while (pa[y] != z) {
                y = pa[y];
            }
            trk[x] = trk[y] = true;
        }
        u = z;
    }
    cout << "! " << u+1 << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
