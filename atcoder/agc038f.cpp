#include <bits/stdc++.h>

using namespace std;

struct Dinic {
    using F = int;
    const static F INF = 0x3f3f3f3f; 
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
    F dfs(int u, F lim) {
        if (u == t) return lim;
        F tot = 0;
        for (int& i = cur[u]; i != -1; i = e[i].bro) {
            int v = e[i].v;
            if (e[i].cap != 0 && d[v] == d[u] + 1) {
                int flow = dfs(v, min(e[i].cap, lim-tot));
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


// hard part is how to form it as project selection problem.
// let a=1 mean don't shift, b=1 mean shift
// x==i or y==i is easy to understand.
// for else part, i!=x!=y!=i, (a,b) if (1,0) our profit -1. so add (a->b) a feasible
// if x==y add another (0,1) (b->a) feasible.
// thus complexity is lower
//
// any much more rigorous proof?
void solve() {
    int n; cin >> n;
    vector<int> p(n), q(n);
    for (auto& x: p) {
        cin >> x;
    }
    for (auto& x: q) {
        cin >> x;
    }
    int s = 0;
    int cyc_cnt = 0;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        if (!a[i] && p[i] != i) {
            cyc_cnt++;
            for (int x = i; !a[x]; x = p[x]) {
                a[x] = cyc_cnt;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (!b[i] && q[i] != i) {
            cyc_cnt++;
            for (int x = i; !b[x]; x = q[x]) {
                b[x] = cyc_cnt;
            }
        }
    }
    int t = cyc_cnt + 1;
    Dinic mc(t+1, s, t);
    int res = 0;
    for (int i = 0; i < n; i++) {
        int x = p[i], y = q[i];
        if (x == i && y == i) continue;
        res++;
        if (x == i) mc.add(s, b[i], 1);
        else if (y == i) mc.add(a[i], t, 1);
        else {
            mc.add(a[i], b[i], 1);
            if (x == y) mc.add(b[i], a[i], 1);
        }
    }
    res -= mc.flow();
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
