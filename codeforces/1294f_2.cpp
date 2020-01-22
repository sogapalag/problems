#include <bits/stdc++.h>

using namespace std;

struct Tree {
    int n;
    vector<vector<int>> g;
    vector<int> sz, pa, depth, sta, fin, tour;
    int tim;
    Tree(int _n) : n(_n)
        , g(n)
        , sz(n)
        , pa(n, -1)
        , depth(n)
        , sta(n)
        , fin(n)
        {
        tour.reserve(n);
        input(); 
    }

    inline void add(int u, int v) {
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    void input() {
        for (int _ = 1; _ < n; _++) {
            int x,y;
            cin >> x >> y;
            --x; --y; // to 0-based
            add(x,y);
        }
    }
    void basic_dfs(int u, int p) {
        //if (pa[u] != -1) g[u].erase(find(g[u].begin(), g[u].end(), pa[u]));
        sta[u] = tim++;
        sz[u] = 0;
        tour.emplace_back(u);
        for (int& v: g[u]) if(v!=p){
            pa[v] = u;
            depth[v] = depth[u] + 1;
            basic_dfs(v,u);
            sz[u] += sz[v];
        }
        ++sz[u];
        fin[u] = tim;
    }

    // diamter must belong some optim
    void solve() {
        // find diamter
        tim = 0; basic_dfs(0,-1);
        int i0 = max_element(depth.begin(), depth.end()) - depth.begin();
        fill(depth.begin(), depth.end(), 0);
        tour.clear();
        basic_dfs(i0, -1);
        int i1 = max_element(depth.begin(), depth.end()) - depth.begin();
        int len = depth[i1];
        vector<bool> trk(n);
        queue<int> q;
        {// multi source bfs
            int x = i1;
            while (x!=i0) {
                q.push(x); trk[x] =1;
                x = pa[x];
            }q.push(i0); trk[i0]=1;
            fill(depth.begin(), depth.end(), 0);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v:g[u])if(!trk[v]){
                    depth[v] = depth[u] + 1;
                    q.push(v); trk[v] =1;
                }
            }
            int i2 = max_element(depth.begin(), depth.end()) - depth.begin();
            int res = len + depth[i2];
            if (i2 == i0 || i2 == i1) {
                i2 = 0;
                while (i2==i0||i2==i1) {
                    i2++;
                }
            }
            cout << res << "\n";
            cout << i0+1 << ' ' << i1+1 << ' ' << i2+1;
        }
    }
};

void solve() {
    int n; cin >> n;
    Tree tr(n); tr.solve();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
