#include <bits/stdc++.h>

using namespace std;

struct MCMF {
    using F = int; const static F INF = 0x3f3f3f3f;
    // using F = long long; const static F INF = 0x3f3f3f3f3f3f3f3f;
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

int eid[40][40][2];

// 网络流24题 火星探险问题
void solve() {
    int n,m,k;
    cin >> k >> m >> n;
    auto id = [&](int i, int j, int out){
        return i*m+j + out*(n*m);
    };
    int S = id(0,0,0), T = id(n-1,m-1,1);
    MCMF g(T+1, S, T);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x; cin >> x;
            if (x == 1) continue;
            if (x == 0) {
                g.add(id(i,j,0), id(i,j,1), k);
            } else {
                g.add(id(i,j,0), id(i,j,1), 1, -1); // stone
                if (k>0) g.add(id(i,j,0), id(i,j,1), k-1);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int _:{0,1}) {//_:dir
                int x = i + (_^1);
                int y = j + (_);
                if (x < n && y < m) {
                    eid[i][j][_] = g.e.size();
                    g.add(id(i,j,1), id(x,y,0), k);
                }
            }
        }
    }
    int flow = g.mcmf().first;
    if (flow == 0) {
        cout << "\n"; return;
    }
    assert(flow == k);

    for (int t = 1; t <= k; t++) {
        // trace / cancel flow
        int i = 0, j = 0;
        while (i!=n-1 || j!=m-1) {
            for (int _:{0,1}) {
                int e = eid[i][j][_];
                if (e && g.e[e^1].cap) {
                    g.e[e^1].cap--;
                    cout << t << ' ' << _ << '\n';
                    i += _^1;
                    j += _;
                    break;
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
