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

    // u dep on v: [0..n)
    // i.e. u implies v
    void add_dep(int u, int v) {
        mc.add(u, v, 1);
        // since each cell cost 1, cap=1 is sufficient-feasible.
        // 607ms->586ms. not significantly fast
    }

    F profit() {
        return positive - mc.flow();
    }
    // A\{s} := s_achivable
    bool chosen(int i) const {
        return mc.d[i] != -1;
    }
};

bool del[222][222];
// horse/knight jump/move
int dx[8] = {1,-1,1,-1,2,-2,2,-2};
int dy[8] = {2,2,-2,-2,1,1,-1,-1};
// 网络流24题 骑士共存问题
// check out move-graph https://en.wikipedia.org/wiki/Knight_(chess)
// almost same p2774, sep by parity, the difference is {dx,dy}
void solve() {
    int n,m;
    cin >> n >> m;
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        del[x][y] = true;
    }
    ProjectSelection ps(n*n);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (del[i][j])continue;
            if ((i+j)&1) {
                ps.add_proj(i*n+j, 1);
                for (int _ = 0; _ < 8; _++) {
                    int x = i + dx[_];
                    int y = j + dy[_];
                    if (0<=x&&x<n && 0<=y&&y<n && !del[x][y]) {
                        ps.add_dep(i*n+j, x*n+y);
                    }
                }
            } else {
                ps.add_proj(i*n+j, -1); sum += 1;
            }
        }
    }
    int res = ps.profit() + sum;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
