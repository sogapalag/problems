#include <bits/stdc++.h>

using namespace std;

const int N = 2e5+10; 
pair<int,int> dp[N][3], up[N];

struct Tree {
    int n;
    vector<vector<int>> g;
    vector<int> sz, pa, depth, sta, fin, tour, deg;
    int tim;
    Tree(int _n) : n(_n)
        , g(n)
        , sz(n)
        , pa(n, -1)
        , depth(n)
        , sta(n)
        , fin(n)
        , deg(n)
        {
        tour.reserve(n);
        input(); 
        //tim = 0; basic_dfs(0);
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
            deg[x]++; deg[y]++;
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

    void solve() {
        int root = -1;
        vector<int> leaf;
        for (int i = 0; i < n; i++) {
            if (deg[i]==1)leaf.push_back(i);
            else root = i;
        }
        assert(root!=-1);
        if (leaf.size() <= 3) {
            if (leaf.size()<3) leaf.push_back(root);
            cout << n-1 << '\n';
            for (int u: leaf) cout << u+1 << ' '; ///  +1, forgot
            return;
        }
        tim = 0; basic_dfs(root);

        memset(dp, -1, sizeof dp);
        int res = 0;
        int certi[3];
        for (int _ = n-1; _ >= 0; _--) {
            int u = tour[_];
            for (int v: g[u]) {
                auto p = dp[v][0];
                p.first++;
                if (p > dp[u][2]) dp[u][2] = p;
                for (int i: {1,0}) 
                    if (dp[u][i+1] > dp[u][i])
                        swap(dp[u][i+1], dp[u][i]);
            }
            if (dp[u][2].first) {
                int sum = 0;
                for (int i:{0,1,2}) sum += dp[u][i].first;
                if (sum > res) {
                    res = sum;
                    for (int i:{0,1,2}) certi[i]=dp[u][i].second;
                }
            }
            if (deg[u] == 1) dp[u][0] = {0, u};
        }
        up[root] = {0, root};
        for (int u: tour) {
            for (int v: g[u]) {
                auto p = dp[u][0];
                // still can occur. v can have many equal max. need to ensure x not in sub(v)
                int x = p.second;
                if (p.first == dp[v][0].first + 1 && sta[v]<=sta[x] && fin[x]<=fin[v]) p = dp[u][1];
                p = max(p, up[u]);
                p.first++;
                int sum = p.first;
                for (int i:{0,1}) sum += dp[v][i].first;
                if (sum > res) {
                    res = sum;
                    for (int i:{0,1}) certi[i] = dp[v][i].second;
                    certi[2] = p.second;
                }
                up[v] = p;
            }
        }
        cout << res << "\n";
        for (int i:{0,1,2}) cout << certi[i]+1 << ' ';
    }
};

// there exist u, {a,b,c}intersect
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
