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

// use flow to determine left[i]  i=[1..n)
// use dfs to find pa[i]
// if find obvious form a tree.
// but if not, why cannot be a tree, or a tree must could find?
// proof:
// one can view this, each edge v is deter but not u. if exist tree. which v not fall into i, meet our v=left[i]
// we can always swap subtree to finally get new tree sats. left[i]
//   i.e. in one step v=left[i], if \E tree v'=left[i]
//      if u'=v, swap(u',v') is enough, since direction is irrelevant
//      else swap v, v' subtree. thus create new tree with v=left[i].
void solve() {
    int n; cin >> n;
    int S = 0, T = 2*n;
    Dinic mf(T+1, S, T);
    vector<vector<int>> g(n+1);
    vector<int> left(n);
    vector<bool> trk(n+1, false);
    for (int i = 1; i < n; i++) {
        int c; cin >> c;
        for (int _ = 0; _ < c; _++) {
            int x; cin >> x;
            mf.add(x, n+i, 1);
            g[x].push_back(i);
        }
    }

    int root = n;
    for (int i = 1; i <= n; i++) {
        if (i != root) mf.add(S, i, 1);
    }
    for (int i = 1; i < n; i++) {
        mf.add(n+i, T, 1);
    }
    if (mf.flow() != n-1) {
        cout << -1; return;
    }
    for (int i = 1; i < n; i++) {
        for (int p = mf.pos[n+i]; p != -1; p = mf.e[p].bro) {
            if (mf.e[p].cap && mf.e[p].v <= n) {
                left[i] = mf.e[p].v;
            }
        }
    }

    vector<int> pa(n);
    function<void(int)> dfs = [&](int l){
        trk[l] = true;
        for (int r: g[l])if(!trk[left[r]]){
            pa[r] = l;
            dfs(left[r]);
        }
    };
    dfs(root);
    for (int i = 1; i <= n; i++) {
        if (!trk[i]) {
            cout << -1; return;
        }
    }
    for (int i = 1; i < n; i++) {
        cout << pa[i] << ' ' << left[i] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
