#include <bits/stdc++.h>

using namespace std;

struct Dsu {
    int n;
    vector<int> p;
    
    Dsu(int _n) : n(_n)
        , p(n)
    {
        init();
    }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
    }
    inline int find(int x) {
        return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline bool join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        p[y] = x; return true;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
};
struct Tree {
    int n;
    vector<vector<int>> g;
    vector<int> sz, pa, depth, sta, fin, tour;
    vector<int> a, dp;
    int tim = 0;
    Tree(int _n) : n(_n)
        , g(n)
        , sz(n)
        , pa(n, -1)
        , depth(n)
        , sta(n)
        , fin(n)
        , a(n, 1e9+10)
        , dp(n, 2e9+10)
        {
        tour.reserve(n);
        //input(); 
        //tim = 0; basic_dfs(0);
        //build_lca();
    }
    int L;
    vector<vector<int>> pa_up;
    int root = 0;
    void build_lca() {
        L = 0; while ((1<<L) < n-1) L++;
        pa_up = vector<vector<int>>(L+1, vector<int>(n));
        pa[root] = root; // root-self
        for (int u: tour) {
            pa_up[0][u] = pa[u];
            for (int j = 1; j <= L; j++) {
                pa_up[j][u] = pa_up[j-1][ pa_up[j-1][u] ];
            }
        }
    }

    inline void add(int u, int v) {
        g[u].emplace_back(v);
        //g[v].emplace_back(u);
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
        //if (pa[u] != -1) g[u].erase(find(g[u].begin(), g[u].end(), pa[u]));
        sta[u] = tim++;
        tour.emplace_back(u);
        for (int& v: g[u]) {
            pa[v] = u;
            depth[v] = depth[u] + 1;
            basic_dfs(v);
            dp[u] = min(dp[u], dp[v]);
            sz[u] += sz[v];
        }
        ++sz[u];
        fin[u] = tim;
    }
    inline bool is_ancestor(int u, int v) {
        return sta[u] <= sta[v] && fin[v] <= fin[u];
    }
    inline int lca(int u, int v) {
        if (is_ancestor(u, v)) return u;
        if (is_ancestor(v, u)) return v;
        for (int j = L; j >= 0; j--) {
            if(!is_ancestor(pa_up[j][u], v))
                u = pa_up[j][u];
        }
        return pa_up[0][u];
    }
    int dist(int u, int v) {
        return depth[u] + depth[v] - 2*depth[lca(u,v)];
    }
    int goup(int u, int step) {
        for (int j = L; j >= 0; j--) {
            if (step>>j&1) u = pa_up[j][u];
        }
        return u;
    }

    int query(int x, int h) {
        for (int j = L; j >= 0; j--) {
            if (depth[x]-(1<<j) >= 0 && a[ pa_up[j][x] ] > h) x = pa_up[j][x];
        }
        return dp[x];
    }
    void solve() {
        basic_dfs(root = n-1);
        build_lca();
        int las = 0;
        int q, K, S;
        cin >> q >> K >> S;
        int n = (this->n+1)/2;
        while (q--) {
            int x, h;
            cin >> x >> h;
            x = (0ll+x + K*las - 1) % n;
            h = (0ll+h + K*las) % (S+1);
            las = query(x, h);
            cout << las << "\n";
        }
    }
};

struct State {
    int d,x;
    State() {}
    State(int _d, int _x) : d(_d), x(_x) {}
    bool operator<(const State& _oth) const {
        return d > _oth.d;
    }
};
// Kruskal 重构树: https://oi-wiki.org/graph/mst/#kruskal_1
// each edge of mst, c-to a node
// i.e. n leaves + (n-1) inner-nodes
// properties:
//   any vert-chain, weight monotonic. i.e. tree is binary-heap
//   max w(x,y) = w[lca]
//   compo of x with some weight-limit, are all leaves of subtree[u], where u is the min-pa_up fit limit
void solve() {
    int n,m;
    cin >> n >> m;
    vector<tuple<int,int,int>> es(m);
    vector<vector<pair<int,int>>> g(n);
    for (int i = 0; i < m; i++) {
        int x,y,z,h;
        cin >> x >> y >> z >> h;
        --x;--y;
        es[i] = {x,y,h};
        g[x].emplace_back(y, z);
        g[y].emplace_back(x, z);
    }

    vector<int> d(n,2e9+10);
    priority_queue<State> pq;
    pq.emplace(d[0]=0, 0);
    while (!pq.empty()) {
        auto _ = pq.top(); pq.pop();
        int z = _.d, x = _.x;
        if (d[x] < z) continue;
        for (auto [y,w]: g[x]) {
            if (d[y] > z+w) {
                d[y] = z+w;
                pq.emplace(d[y],y);
            }
        }
    }

    Dsu dsu(n*2-1);
    sort(es.begin(), es.end(), [&](auto& u, auto& v){
        return get<2>(u) > get<2>(v); // greater
    });
    Tree tr(n+n-1);
    for (int i = 0; i < n; i++) {
        tr.dp[i] = d[i];
    }
    int cnt = n;
    for (auto [x,y,z]:es) {
        x = dsu.find(x);
        y = dsu.find(y);
        if (x != y) {
            tr.add(cnt, x);
            tr.add(cnt, y);
            tr.a[cnt] = z;
            dsu.p[x]=dsu.p[y]=cnt;
            //dsu.join(cnt, x);
            //dsu.join(cnt, y);
            ++cnt;
        }
    }

    tr.solve();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
