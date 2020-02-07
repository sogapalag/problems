#include <bits/stdc++.h>

using namespace std;

struct Tree {
    int n;
    vector<vector<int>> g;
    vector<int> sz, pa, depth, sta, fin, tour, arm;
    int tim;
    Tree(int _n) : n(_n)
        , g(n)
        //, sz(n)
        , pa(n, -1)
        , depth(n)
        //, sta(n)
        //, fin(n)
        , arm(n)
        {
        //tour.reserve(n);
        input(); 
        tim = 0; basic_dfs(0);
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
    void basic_dfs(int u) {
        if (pa[u] != -1) g[u].erase(find(g[u].begin(), g[u].end(), pa[u]));
        //sta[u] = tim++;
        //tour.emplace_back(u);
        for (int& v: g[u]) {
            pa[v] = u;
            depth[v] = depth[u] + 1;
            basic_dfs(v);
            arm[u] = max(arm[u], arm[v] + 1);
            //sz[u] += sz[v];
            // skew max-height
            if (arm[v] > arm[g[u][0]]) swap(v, g[u][0]);
        }
        //++sz[u];
        //fin[u] = tim;
    }

    vector<vector<int>> cnt;
    vector<int> id;
    void dfs(int u) {
        bool is_first = true;
        for (int v: g[u]) {
            dfs(v);
            if (is_first) {
                cnt[u] = move(cnt[v]);
                id[u] = id[v];
                is_first = false;
            } else {
                int m0 = cnt[u].size();
                int m1 = cnt[v].size();
                // m0-1, closest is back
                for (int i = m1; i >= 1; i--) {
                    cnt[u][m0-i] += cnt[v][m1-i];
                    if (cnt[u][m0-i] >= cnt[u][id[u]]) {
                        id[u] = m0-i;
                    }
                }
            }
        }
        cnt[u].push_back(1);
        if (1 >= cnt[u][id[u]]) id[u] = cnt[u].size()-1;
    }
    void solve() {
        cnt.resize(n);
        id.resize(n);
        dfs(0);
        for (int i = 0; i < n; i++) {
            int res = arm[i] - id[i];
            cout << res << '\n';
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
