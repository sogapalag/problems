#include <bits/stdc++.h>

using namespace std;
using ll=long long;
// edges matter
struct HLD {
    using CT = int;
    struct Edge {
        int u, v;
        CT cost;
        Edge() {}
        Edge(int _u, int _v, CT _cost) : u(_u), v(_v), cost(_cost) {}
    };
    int n;
    vector<vector<int>> g;
    vector<Edge> e;
    vector<int> sz, pa, depth, sta, fin, heavy, top, tour, edge_tour, ord;
    int tim;
    vector<ll> sum;
    HLD(int _n) : n(_n)
        , g(n)
        , sz(n, 1)
        , pa(n, -1)
        , depth(n)
        , sta(n)
        , fin(n)
        , heavy(n, -1)
        , top(n)
        , ord(n)
        , sum(n)
        {
        tour.reserve(n);
        e.reserve(n); e.emplace_back(); // root-up-virtual
        edge_tour.reserve(n); edge_tour.emplace_back(); // virtual
        input(); 
    }

    inline void add(int u, int v, CT cost) {
        g[u].emplace_back(e.size());
        g[v].emplace_back(e.size());
        e.emplace_back(u, v, cost);
    }
    void input() {
        for (int _ = 1; _ < n; _++) {
            int x,y; CT z;
            cin >> x >> y >> z;
            --x; --y; // to 0-based
            add(x,y,z);
        }
    }
    inline int ch(int u, int i) {
        return e[i].u ^ e[i].v ^ u;
    }
    void dfs(int u, int past_edge = -1) {
        if (past_edge != -1) g[u].erase(find(g[u].begin(), g[u].end(), past_edge));
        for (int& i: g[u]) {
            int v = ch(u, i);
            pa[v] = u;
            depth[v] = depth[u] + 1;
            dfs(v, i);
            sz[u] += sz[v];
            // heavy skew left, thus chain consective on sta
            int& j = g[u][0];
            if (sz[v] > sz[ch(u,j)]) swap(i, j);
        }
    }
    // sta*tour = I, ord*edge_tour = I
    void hld(int u) {
        sta[u] = tim++;
        tour.emplace_back(u);
        for (int i: g[u]) {
            edge_tour.emplace_back(i);
            ord[i] = tim;
            int v = ch(u, i);
            top[v] = (v == ch(u, g[u][0]) ? heavy[u] = v, top[u] : v); // #h=1
            //top[v] = (sz[v] >= (sz[u]+1)/2 ? heavy[u] = v, top[u] : v); // #h<=1
            hld(v);
        }
        fin[u] = tim;
    }
    void build(int root = 0) {
        dfs(root);
        tim = 0; top[root] = root; hld(root);
        // pref
        for (int i = 1; i < n; i++) {
            sum[i] = sum[i-1] + e[edge_tour[i]].cost;
        }
    }
    inline void across_light(int& v) {
        v = pa[top[v]];
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            sta[u] < sta[v] ? across_light(v) : across_light(u);
        }
        return sta[u] < sta[v] ? u : v;
    }

    using F = function<void(int,int)>; // range operation tim(0)-based [l..r)
    // [u..v]
    void for_v_path(int u, int v, F f) {
        while (true) {
            if (sta[u] > sta[v]) swap(u, v);
            f(max(sta[top[v]], sta[u]), sta[v]+1);
            if (top[u] == top[v]) return;
            across_light(v);
        }
    }
    // [u..v], Caution: tim(0), edge_tour/cost on [1..n) alias
    void for_e_path(int u, int v, F f) {
        while (true) {
            if (sta[u] > sta[v]) swap(u, v);
            if (top[u] == top[v]) {
                if (u != v) f(sta[u]+1, sta[v]+1);
                return;
            }
            f(sta[top[v]], sta[v]+1);
            across_light(v);
        }
    }
    void for_v_sub(int u, F f, bool exclude = 0) {
        f(sta[u] + exclude, fin[u]);
    }
    void for_e_sub(int u, F f) {
        f(sta[u]+1, fin[u]);
    }
    void process_query() {
        string op;
        while (cin >> op) {
            if (op[1] == 'O') return;
            if (op[0] == 'D') {
                int u, v;
                cin >> u >> v;
                u--;v--;
                ll res = 0;
                for_e_path(u,v, [&](int l, int r){
                        res += sum[r-1] - sum[l-1];
                        });
                cout << res << "\n";
            } else {
                int u,v,k;
                cin >> u >> v >> k;
                u--;v--;k--;
                int z = lca(u,v);
                if (depth[u] - depth[z] < k) {
                    k = depth[u]-depth[z] + depth[v]-depth[z] - k;
                    swap(u,v);
                }
                while (depth[u] - depth[top[u]] < k) {
                    k -= depth[u] - depth[top[u]] + 1;
                    across_light(u);
                }
                int down = depth[u] - depth[top[u]] - k;
                u = tour[sta[top[u]] + down];
                cout << u+1 << "\n";
            }
        }
    }
};
// off-line could use lca+rmq(st)
// hld is overkill
void solve() {
    int n; cin >> n;
    HLD hld(n);
    hld.build();
    hld.process_query();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
