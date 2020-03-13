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
int eid[1024][24];

// 网络流24题 试题库问题
void solve() {
    int k,n;
    cin >> k >> n;
    int S = n+k+1, T = S + 1;
    Dinic mf(T+1, S, T);
    for (int i = 0; i < n; i++) {
        mf.add(S, i, 1);
    }
    int tot = 0;
    for (int i = 0; i < k; i++) {
        int x; cin >> x;
        tot += x;
        mf.add(n+i, T, x);
    }
    for (int i = 0; i < n; i++) {
        int m; cin >> m;
        for (int _ = 0; _ < m; _++) {
            int j; cin >> j; j--;
            eid[i][j] = mf.e.size();
            mf.add(i, n+j, 1);
        }
    }
    if (mf.flow() < tot) {
        cout << "No Solution!";
        return;
    }
    vector<vector<int>> res(k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            int x = eid[i][j];
            if (x && mf.e[x].cap == 0) res[j].push_back(i);
        }
    }
    for (int j = 0; j < k; j++) {
        cout << j+1 << ": ";
        for (auto& i: res[j]) {
            cout << i+1 << ' ';
        }
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
