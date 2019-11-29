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
        //for (int l = 0; l < n; l++) {
        //    g.add(s, l, 1);
        //}
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

// we only care k < deg <= 2*k, since > 2*k invalid, <=k valid for sure.
// and there exist >= (deg-k) pairs same color.
// and we can only care =. since key observation, once an edge used for contribute some vertex pair. it can never contribute to other vertex.
// so if there is solution, there exist "=" solution. since color range is large.
void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    vector<int> deg(n, 0);
    vector<pair<int, int>> es(m);
    for (int i = 0; i < m; i++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        deg[x]++; deg[y]++;
        es[i] = {x,y};
    }
    auto gg = [&](){
        for (int _ = 0; _ < m; _++) {
            cout << "0 ";
        }cout << "\n";
    };
    if (*max_element(deg.begin(), deg.end()) > 2*k) {
        gg(); return;
    }

    BipartiteMaching bm(n, m);
    int need = 0;
    for (int i = 0; i < n; i++) {
        if (deg[i] > k) {
            int twins = 2*(deg[i]-k);
            need += twins;
            bm.g.add(bm.s, i, twins); // g.
        }
    }
    for (int i = 0; i < m; i++) {
        int x,y;
        tie(x,y) = es[i];
        if (deg[x] > k) {
            bm.add(x, i); // 1
        }
        if (deg[y] > k) {
            bm.add(y, i);
        }
    }

    int flow = bm.match();
    if (flow < need) {
        gg(); return;
    }

    auto& left = bm.left;
    vector<int> res(m);
    int cnt = 1;
    for (int r = 0; r < m; r++) {
        if (left[r] == -1) {
            res[r] = cnt++;
        }
    }
    cnt = 2048;
    for (int l = 0; l < n; l++) {
        for (int j = 0; j < m; j++) {
            if (left[j] == l) {
                res[j] = cnt>>1; cnt++;
            }
        }
    }

    for (auto& x: res) {
        cout << x << ' ';
    }cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
