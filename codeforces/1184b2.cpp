#include <bits/stdc++.h>

using namespace std;

struct Dinic {
    using F = int; const static F INF = 0x3f3f3f3f; 
    //using F = long long; const static F INF = 0x3f3f3f3f3f3f3f3f; 
    struct Edge {
        int v, bro; F cap;
        Edge() {}
        Edge(int _v, int _bro, F _cap) : v(_v), bro(_bro), cap(_cap) {}
    };
    vector<Edge> e;
    vector<int> pos, cur;
    int n, s, t, m;
    Dinic(int _n, int _s, int _t) : n(_n), s(_s), t(_t), m(0) {
        pos.assign(n, -1);
        cur.resize(n);
        d.resize(n);
        e.reserve(4e5);
    }
    void add(int u, int v, F c=INF) {
        assert(u < n && v < n);
        e.emplace_back(v, pos[u], c); pos[u] = m++;
        e.emplace_back(u, pos[v], 0); pos[v] = m++;
    }
    vector<int> d;
    // build layer graph
    bool bfs() {
        fill(d.begin(), d.end(), -1);
        d[s] = 0;
        queue<int> q; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = cur[u] = pos[u]; i != -1; i = e[i].bro) {
                int v = e[i].v;
                if (d[v] == -1 && e[i].cap != 0) {
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        }
        return d[t] != -1;
    }
    // find blocking flow
    F dfs(int u, F lim) {
        if (u == t) return lim;
        F tot = 0;
        for (int& i = cur[u]; i != -1; i = e[i].bro) {
            int v = e[i].v;
            if (e[i].cap != 0 && d[v] == d[u] + 1) {
                F flow = dfs(v, min(e[i].cap, lim-tot));
                tot += flow;
                e[i].cap -= flow;
                e[i^1].cap += flow;
                if (tot == lim) return lim;
            }
        }
        return tot;
    }
    F flow() {
        F res = 0;
        while (bfs()) {
            res += dfs(s, INF);
        }
        return res;
    }
};

struct BipartiteMaching {
    int n, m; // #l, #r
    int s, t;
    Dinic g;
    vector<int> right, left;
    BipartiteMaching(int _n, int _m) : n(_n), m(_m)
        , s(n+m)
        , t(n+m+1)
        , g(n+m+2, s, t)
        , right(n, -1)
        , left(m, -1)
    {
        for (int l = 0; l < n; l++) {
            g.add(s, l, 1);
        }
        for (int r = 0; r < m; r++) {
            g.add(n+r, t, 1);
        }
    }

    // l: [0..n),  r: [0..m)
    void add(int l, int r) {
        g.add(l, n+r, 1);
    }

    int match() {
        int res = g.flow();
        for (int r = 0; r < m; r++) {
            for (int i = g.pos[n+r]; i != -1; i = g.e[i].bro) {
                if (g.e[i].cap && g.e[i].v < n) {
                    right[left[r] = g.e[i].v] = r;
                    break;
                }
            }
        }
        return res;
    }

};

struct Bip {
    int n,m; // #l, #r
    vector<vector<int>> g;
    vector<int> left;
    vector<bool> trk;

    Bip() {}
    Bip(int _n) : n(_n), m(_n) {
        init();
    }
    Bip(int _n, int _m) : n(_n), m(_m) {
        init();
    }
    void init() {
        g.resize(n);
        left.assign(m, -1);
        trk.assign(n, false);
    }
    inline void add(int l, int r) {
        assert(0 <= l && l < n);
        assert(0 <= r && r < m);
        g[l].emplace_back(r);
    }

    bool dfs(int l) {
        if (trk[l]) return false;
        trk[l] = true;
        for (int r: g[l]) {
            if (left[r] == -1 || dfs(left[r])) {
                left[r] = l;
                return true;
            }
        }
        return false;
    }
    int match() {
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            fill(trk.begin(), trk.end(), false);
            if (dfs(i)) cnt++;
        }
        return cnt;
    }
};

const int INF = 0x3f3f3f3f;
const int N = 111; 
int d[N][N];

void solve() {
    int n,m;
    cin >> n >> m;
    memset(d, INF, sizeof d);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        d[x][y] = d[y][x] = 1;
    }
    for (int i = 0; i < n; i++) {
        d[i][i] = 0;
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (d[i][k] < INF && d[k][j] < INF) {// for negative
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }

    int s,b,k,h;
    cin >> s >> b >> k >> h;
    vector<int> x(s), a(s), f(s), y(b), g(b);
    for (int i = 0; i < s; i++) {
        cin >> x[i] >> a[i] >> f[i];
        --x[i];
    }
    for (int i = 0; i < b; i++) {
        cin >> y[i] >> g[i];
        --y[i];
    }

    //BipartiteMaching bm(s,b); // 1200ms
    Bip bm(s,b); // 350ms
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < b; j++) {
            int u = x[i], v = y[j];
            if (a[i] >= g[j] && d[u][v] <= f[i]) {
                bm.add(i, j);
            }
        }
    }
    
    int mat = bm.match();
    long long res = 1ll * mat * k;
    if (k > h) {
        res = min(res, 1ll * h * s);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
