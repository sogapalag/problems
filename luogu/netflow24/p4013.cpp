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

int a[33][50];
int id[33][50][2];
#define rep(i) for(int i:{0,1})

// 网络流24题 数字梯形问题
// unclear statement. note even for 2.3. start always use m of m. i.e. first each differ
void solve() {
    int n,m;
    cin >> m >> n;
    int S = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m+i; j++) {
            cin >> a[i][j];
            rep(_)id[i][j][_] = S++;
        }
    }
    int T = S + 1;

    {//1
        MCMF g(T+1, S, T);
        for (int j = 0; j < m; j++) {
            g.add(S, id[0][j][0], 1);
        }
        for (int i = 0; i < n-1; i++) {
            for (int j = 0; j < m+i; j++) {
                rep(_) g.add(id[i][j][1], id[i+1][j+_][0], 1);
            }
        }
        for (int j = 0; j < m+n-1; j++) {
            g.add(id[n-1][j][1], T, 1);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m+i; j++) {
                g.add(id[i][j][0], id[i][j][1], 1, -a[i][j]);
            }
        }
        auto res = - g.mcmf().second;
        cout << res << "\n";
    }

    {//2
        MCMF g(T+1, S, T);
        for (int j = 0; j < m; j++) {
            g.add(S, id[0][j][0], 1);
        }
        for (int i = 0; i < n-1; i++) {
            for (int j = 0; j < m+i; j++) {
                rep(_) g.add(id[i][j][1], id[i+1][j+_][0], 1);
            }
        }
        for (int j = 0; j < m+n-1; j++) {
            g.add(id[n-1][j][1], T, m); // m
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m+i; j++) {
                g.add(id[i][j][0], id[i][j][1], m, -a[i][j]); // m
            }
        }
        auto res = - g.mcmf().second;
        cout << res << "\n";
    }

    {//3
        MCMF g(T+1, S, T);
        for (int j = 0; j < m; j++) {
            g.add(S, id[0][j][0], 1);
        }
        for (int i = 0; i < n-1; i++) {
            for (int j = 0; j < m+i; j++) {
                rep(_) g.add(id[i][j][1], id[i+1][j+_][0], m); // m
            }
        }
        for (int j = 0; j < m+n-1; j++) {
            g.add(id[n-1][j][1], T, m); // m
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m+i; j++) {
                g.add(id[i][j][0], id[i][j][1], m, -a[i][j]); // m
            }
        }
        auto res = - g.mcmf().second;
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
