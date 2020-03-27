#include <bits/stdc++.h>

using namespace std;

struct Dinic {
    //using F = int; const static F INF = 0x3f3f3f3f; 
    using F = long long; const static F INF = 0x3f3f3f3f3f3f3f3f; 
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

struct ProjectSelection {
    int n;
    int s,t;
    Dinic mc;
    using F = Dinic::F;
    F positive;

    ProjectSelection(int _n) : n(_n)
        , s(n)
        , t(n+1)
        , mc(n+2, s, t)
        , positive(0)
    {}

    // i: [0..n)
    void add_proj(int i, F profit) {
        if (profit >= 0) {
            mc.add(s, i, profit);
            positive += profit;
        } else {
            mc.add(i, t, -profit);
        }
    }
    // chosen NOT-equiv edge.cap==0
    // {chosen} = A-{s} = s-achivable. by min-cut
    bool chosen(int i) {
        return mc.d[i] != -1;
    }

    // u dep on v: [0..n)
    // i.e. u implies v
    void add_dep(int u, int v) {
        mc.add(u, v);
    }

    F profit() {
        return positive - mc.flow();
    }
};
// 网络流24题 太空飞行计划问题
void solve() {
    int n,m;
    {
        string s; getline(cin, s);
        stringstream sin(s);
        sin >> n >> m;
    }
    ProjectSelection ps(n + m);
    for (int i = 0; i < n; i++) {
        string s; getline(cin, s);
        stringstream sin(s);
        int x; sin >> x;
        ps.add_proj(i, x);
        while (sin >> x){
            x--;
            ps.add_dep(i, n+x);
        }
    }
    {
        string s; getline(cin, s);
        stringstream sin(s);
        for (int i = 0; i < m; i++) {
            int x; sin >> x;
            ps.add_proj(i+n, -x);
        }
    }
    auto res = ps.profit();
    for (int i = 0; i < n; i++) {
        if (ps.chosen(i)) {
            cout << i+1 << ' ';
        }
    }cout << '\n';
    for (int i = 0; i < m; i++) {
        if (ps.chosen(n+i)) {
            cout << i+1 << ' ';
        }
    }cout << '\n';
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
