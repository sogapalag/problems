#include <bits/stdc++.h>

using namespace std;
using ll=long long;

struct Graph {
    //using CT = int; static const CT INF = 0x3f3f3f3f;
    using CT = long long; static const CT INF = 0x3f3f3f3f3f3f3f3f;
    struct Edge {
        int u, v;
        CT cost;
        Edge(int _u, int _v, CT _cost) : u(_u), v(_v), cost(_cost) {}
    };
    int n, m;
    bool is_digraph;
    vector<vector<int>> g;
    vector<Edge> e;

    Graph(int _n) : n(_n), m(0) {
        assert(n >= 1);
        g.resize(n);
        set_di(false);
    }
    Graph(int _n, int _m, bool _di=false) : n(_n) {
        assert(n >= 1);
        g.resize(n);
        e.reserve(_m);
        m = 0;
        set_di(_di);
        input(_m);
    }
    void set_di(bool _di) {
        is_digraph = _di;
    }
    inline void add(int u, int v, CT cost=1) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        if (is_digraph) {
            //outdeg[u]++; indeg[v]++;
            g[u].emplace_back(m);

        } else {
            //deg[u]++; deg[v]++;
            g[u].emplace_back(m);
            g[v].emplace_back(m);
        }
        e.emplace_back(u, v, cost);
        m++;
    }
    void input(int _m) {
        int u, v; CT c;
        for (int i = 0; i < _m; i++) {
            cin >> u >> v >> c;
            u--; v--; // input 1-based
            add(u, v, c);
        }
    }

    // if multi-source, add dummy SOURCE
    // single source shortest path
    vector<CT> dijkstra(int s) {
        vector<bool> trk(n, false);
        vector<CT> d(n, INF);
        d[s] = 0;
        using pi=pair<CT,int>;
        priority_queue<pi, vector<pi>, greater<pi>> pq;
        pq.push({0, s});
        while (!pq.empty()) {
            CT dis; int u;
            tie(dis, u) = pq.top(); pq.pop();
            if (trk[u])
                continue;
            trk[u] = true;
            for (int i: g[u]) {
                int v = e[i].u ^ e[i].v ^ u;
                if (d[v] > d[u] + e[i].cost) {
                    d[v] = d[u] + e[i].cost;
                    pq.push({d[v], v});
                }
            }
        }
        return d;
    }
};

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
        tim = 0; basic_dfs(0);
        build_lca();
    }
    int L;
    vector<vector<int>> pa_up;
    void build_lca() {
        L = 0; while ((1<<L) < n-1) L++;
        pa_up = vector<vector<int>>(L+1, vector<int>(n));
        pa[0] = 0; // root-self
        for (int u: tour) {
            pa_up[0][u] = pa[u];
            for (int j = 1; j <= L; j++) {
                pa_up[j][u] = pa_up[j-1][ pa_up[j-1][u] ];
            }
        }
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

    void solve() {
    }
};
using pi=pair<int, int> ;
const ll INF = 0x3f3f3f3f'3f3f3f3f; 
const int N = 3e5+10; 
ll dp[20][N][2][2];
// dist: u[s] -> pa[j][u] [t], 

// key: (dijkstra)modify a to dist[u][0<->1], thus for u->v avoid "go back"
void solve() {
    int n; cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<pi> es(n-1);
    vector<array<ll,2>> ws(n-1);
    vector<vector<int>> tr(n);
    for (int i = 0; i < n-1; i++) {
        int x,y;
        ll w0,w1; // ll, not int..
        cin >> x >> y >> w0 >> w1;
        x--;y--;
        es[i] = {x,y};
        ws[i] = {w0,w1};
        tr[x].push_back(i);
        tr[y].push_back(i);
    }
    
    {// to standard
        Graph g(n + 1);
        for (int i = 0; i < n; i++) {
            g.add(n, i, a[i]);
        }
        for (int i = 0; i < n-1; i++) {
            g.add(es[i].first, es[i].second, ws[i][0] + ws[i][1]);
        }
        auto d = g.dijkstra(n);
        for (int i = 0; i < n; i++) {
            a[i] = min(a[i], d[i]);
        }
    }
#define fi first
#define se second
    vector<int> pe(n, -1), pa(n, -1);
    vector<int> tour; tour.reserve(n);
    int tim = 0;
    vector<int> sta(n), fin(n);
    function<void(int)> dfs = [&](int u){
        sta[u] = tim++;
        tour.push_back(u);
        for (int i:tr[u])if(i!=pe[u]) {
            int v = es[i].fi ^ es[i].se ^ u;
            pe[v] = i;
            pa[v] = u;
            dfs(v);
        }
        fin[u] = tim;
    };
    dfs(0);


    int L;
    vector<vector<int>> pa_up;
    {
        L = 0; while ((1<<L) < n) L++;
        pa_up = move(vector<vector<int>>(L+1, vector<int>(n)));
        pa[0] = 0; // root-self
        for (int u: tour) {
            pa_up[0][u] = pa[u];
            for (int j = 1; j <= L; j++) {
                pa_up[j][u] = pa_up[j-1][ pa_up[j-1][u] ];
            }
        }
    }
    auto is_ancestor = [&](int u, int v) -> bool{
        return sta[u] <= sta[v] && fin[v] <= fin[u];
    };
    auto lca = [&](int u, int v) -> int{
        if (is_ancestor(u, v)) return u;
        if (is_ancestor(v, u)) return v;
        for (int j = L; j >= 0; j--) {
            if(!is_ancestor(pa_up[j][u], v))
                u = pa_up[j][u];
        }
        return pa_up[0][u];
    };

    auto mini = [](ll& x, const ll& y){
        if (x > y) x = y;
    };
#define rep(i) for(int i:{0,1})
    {
        memset(dp, 0x3f, sizeof dp);
        for (int u:tour) {
            int i = pe[u];
            if (i != -1) {
                int v = es[i].fi ^ es[i].se ^ u;
                dp[0][u][0][0] = min(ws[i][0], a[u] + ws[i][1] + a[v]);
                dp[0][u][0][1] = min(ws[i][0] + a[v], a[u] + ws[i][1]);
                dp[0][u][1][0] = min(a[u] + ws[i][0], ws[i][1] + a[v]);
                dp[0][u][1][1] = min(a[u] + ws[i][0] + a[v], ws[i][1]);
            }
            for (int j = 1; j <= L; j++) {
                rep(s)rep(t)rep(r){
                    mini(dp[j][u][s][t], dp[j-1][u][s][r] + dp[j-1][ pa_up[j-1][u] ][r][t]);
                }
            }
        }
    }

    auto dist = [&](int u, int v, int s, int t){
        if (u == v) return a[u];
        ll z = lca(u,v);
        ll tmp[2] = {}; tmp[s^1] = a[u];
        for (int j = L; j >= 0; j--) {
            if (!is_ancestor(pa_up[j][u], z)) {
                ll nxt[2];
                rep(y)nxt[y] = min(tmp[0] + dp[j][u][0][y], tmp[1] + dp[j][u][1][y]);
                swap(tmp, nxt);
                u = pa_up[j][u];
            }
        }
        if (u != z) {
            int j = 0;
            ll nxt[2];
            rep(y)nxt[y] = min(tmp[0] + dp[j][u][0][y], tmp[1] + dp[j][u][1][y]);
            swap(tmp, nxt);
            u = pa_up[j][u];
        }

        ll left[2] = {}; swap(left, tmp);

        // right
        swap(u, v); swap(s,t);
        tmp[s^1] = a[u];
        for (int j = L; j >= 0; j--) {
            if (!is_ancestor(pa_up[j][u], z)) {
                ll nxt[2];
                rep(y)nxt[y] = min(tmp[0] + dp[j][u][0][y], tmp[1] + dp[j][u][1][y]);
                swap(tmp, nxt);
                u = pa_up[j][u];
            }
        }
        if (u != z) {
            int j = 0;
            ll nxt[2];
            rep(y)nxt[y] = min(tmp[0] + dp[j][u][0][y], tmp[1] + dp[j][u][1][y]);
            swap(tmp, nxt);
            u = pa_up[j][u];
        }
        return min(left[0]+tmp[0], left[1]+tmp[1]);
    };

    int q; cin >> q;
    while (q--) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        int s = (x&1);
        int t = (y&1);
        x/=2; y/=2;
        cout << dist(x, y, s, t) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
