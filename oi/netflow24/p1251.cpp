#include <bits/stdc++.h>

using namespace std;

struct MCMF {
    //using F = int; const static F INF = 0x3f3f3f3f;
    using F = long long; const static F INF = 0x3f3f3f3f3f3f3f3f;
    struct Edge {
        int v, bro;
        F cap, cost;
        Edge() {}
        Edge(int _v, int _bro, F _cap, F _cost) : v(_v), bro(_bro), cap(_cap), cost(_cost) {}
    };
    vector<Edge> e;
    vector<int> pos, pre;
    vector<F> dis;
    vector<bool> trk;
    int n, s, t, m;
    MCMF(int _n, int _s, int _t) : n(_n), s(_s), t(_t), m(0) {
        pos.assign(n, -1);
        pre.resize(n);
        dis.resize(n);
        trk.resize(n);
        e.reserve(4e5);
    }
    void add(int u, int v, F cap = INF, F cost = 0) {
        assert(u < n && v < n);
        e.emplace_back(v, pos[u], cap, cost); pos[u] = m++;
        e.emplace_back(u, pos[v], 0, -cost);  pos[v] = m++;
    }
    bool spfa() {
        queue<int> q;
        fill(pre.begin(), pre.end(), -1);
        fill(dis.begin(), dis.end(), INF);
        fill(trk.begin(), trk.end(), false);
        dis[s] = 0; trk[s] = true; q.push(s);
        while(!q.empty()){
            int u = q.front(); q.pop(); trk[u] = false;
            for (int i = pos[u]; i != -1; i = e[i].bro){
                int v = e[i].v;
                if (e[i].cap > 0 && dis[v] > dis[u] + e[i].cost){
                    dis[v] = dis[u] + e[i].cost;
                    pre[v] = i;
                    if (!trk[v]){
                        trk[v] = true; q.push(v);
                    }
                }
            }
        }
        return pre[t] != -1;
    }
    pair<F,F> mcmf() {
        F flow = 0, cost = 0;
        while (spfa()) {  // (dijkstra()) {
            F f = INF;
            for (int i = pre[t]; i != -1; i = pre[e[i^1].v])
                f = min(f, e[i].cap);
            for (int i = pre[t]; i != -1; i = pre[e[i^1].v]){
                e[i].cap -= f;
                e[i^1].cap += f;
                cost += e[i].cost * f;
            }
            flow += f;
        }
        return {flow, cost};
    }
};

// 网络流24题  餐巾计划问题
void solve() {
    int n; cin >> n;
    int S = 2*n + 1, T = S + 1;
    MCMF g(T+1, S, T);
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    int c0, d1, c1, d2, c2;
    cin >> c0 >> d1 >> c1 >> d2 >> c2;
    for (int i = 0; i < n; i++) {
        int x = a[i];
        g.add(S,i,x); // for to wash
        g.add(S,i+n,x,c0); // buy
        if (i+1 < n) {
            g.add(i,i+1);
            g.add(i+n, i+n+1);
        }
        if (i + d1 < n) g.add(i, i+d1+n, MCMF::INF, c1);
        if (i + d2 < n) g.add(i, i+d2+n, MCMF::INF, c2);
        g.add(i+n, T, x);
    }
    auto res = g.mcmf().second;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
