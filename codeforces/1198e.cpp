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

// konig: max matching = min vertex cover
void solve() {
    int n,m;
    cin >> n >> m;
    if (m == 0) {
        cout << 0; return;
    }
    vector<int> X, Y;
    vector<pair<int, int>> l(m), r(m);
    for (int i = 0; i < m; i++) {
        int x,y, u,v;
        cin >> x >> y >> u >> v;
        u++;v++;
        l[i] = {x,y};
        r[i] = {u,v};
        X.push_back(x);
        X.push_back(u);
        Y.push_back(y);
        Y.push_back(v);
    }
    // compress to nx*ny grid region
    sort(X.begin(), X.end());
    X.erase(unique(X.begin(), X.end()), X.end());
    sort(Y.begin(), Y.end());
    Y.erase(unique(Y.begin(), Y.end()), Y.end());

    int S = 0;
    int nx = X.size() - 1;
    int ny = Y.size() - 1;
    int T = nx + ny + 1;
    Dinic mf(T+1, S, T);

    for (int i = 1; i <= nx; i++) {
        mf.add(S, i, X[i]-X[i-1]);
    }
    for (int i = 1; i <= ny; i++) {
        mf.add(nx+i, T, Y[i]-Y[i-1]);
    }
    // for each region if black then add edge
    for (int i = 1; i <= nx; i++) {
        for (int j = 1; j <= ny; j++) {
            for (int k = 0; k < m; k++) {
                if (l[k].first <= X[i-1] && X[i] <= r[k].first
                        && l[k].second <= Y[j-1] && Y[j] <= r[k].second) {
                    mf.add(i, nx+j);
                    break;
                }
            }
        }
    }

    int res = mf.flow();
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
