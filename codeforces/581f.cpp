#include <bits/stdc++.h>

using namespace std;

const int N = 5012; 
int dp[N][2][N], convo[2][N];

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
        for (int i = 0; i < n; i++) {
            if (g[i].size() > 1) root = i;
        }
        tim = 0; basic_dfs(root);
    }
    int root;

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
    void basic_dfs(int u) {
        if (pa[u] != -1) g[u].erase(find(g[u].begin(), g[u].end(), pa[u]));
        sta[u] = tim++;
        tour.emplace_back(u);
        for (int& v: g[u]) {
            pa[v] = u;
            depth[v] = depth[u] + 1;
            basic_dfs(v);
            sz[u] += sz[v];
        }
        ++sz[u];
        fin[u] = tim;
    }

#define rep(x) for(int x:{0,1})
    void mini(int& x, int y){
        if (x > y) x = y;
    }
    // dp[u][x][i], co[u]=x, #1-leaf = i, min component
    //  since edge = compon - 1. maintain diff-edge work similar.
    void solve() {
        memset(dp, 0x3f, sizeof dp);
        fill(sz.begin(), sz.end(), 0);
        for (int _ = n-1; _ >= 0; _--) {
            int u = tour[_];
            dp[u][0][0] = 1;
            dp[u][1][g[u].empty()] = 1;
            sz[u]++;
            for (int v:g[u]){
                memset(convo[0], 0x3f, sizeof(int) * (sz[u] + sz[v] + 1));
                memset(convo[1], 0x3f, sizeof(int) * (sz[u] + sz[v] + 1));
                for (int i = 0; i <= sz[u]; i++) {
                    for (int j = 0; j <= sz[v]; j++) {
                        rep(x)rep(y){
                            mini(convo[x][i+j], dp[u][x][i]+dp[v][y][j] + (x^y)-1);
                        }
                    }
                }
                sz[u] += sz[v];
                memcpy(dp[u][0], convo[0], sizeof(int) * (sz[u] + 1));
                memcpy(dp[u][1], convo[1], sizeof(int) * (sz[u] + 1));
            }
        }
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (g[i].empty()) cnt++;
        }
        cout << min(dp[root][0][cnt/2], dp[root][1][cnt/2]) - 1;
    }
};

void solve() {
    int n; cin >> n;
    if (n == 2) {
        cout << 1; return;
    }
    Tree tr(n); tr.solve();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
