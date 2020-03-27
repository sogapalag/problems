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

// 网络流24题 [CTSC1999]家园 / 星际转移问题
// one way is binary search, but we can push-flow.
void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    n += 2;
    const int MOON = n-1; 

    auto id = [&](int x, int t){
        return x + t*n;
    };

    const int LIM = 700; 
    int S = LIM*n, T = S+1;
    Dinic mf(T+1, S, T);
    mf.add(S, 0, k);
    for (int _ = 0; _ < m; _++) {
        int cap; cin >> cap; 
        int sz; cin >> sz;
        vector<int> a(sz);
        for (auto& x: a) {
            cin >> x;
            if (x==-1) x = MOON;
        }
        for (int t = 0; t+1 < LIM; t++) {
            mf.add(id(a[t%sz], t), id(a[(t+1)%sz], t+1), cap);
        }
    }
    for (int i = 0; i < MOON; i++) {
        for (int t = 0; t+1 < LIM; t++) {
            mf.add(id(i,t), id(i,t+1), k); // stay
        }
    }

    const int LOW = 70; 
    int flow = 0;
    for (int t = 1; t < LIM; t++) {
        mf.add(id(MOON, t), T, k);
        flow += mf.flow();
        if (flow == k) {
            cout << t; return;
        }
        // early stop
        if (t >= LOW && flow == 0) {
            cout << 0; return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
