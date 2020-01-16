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
            // don't need max-flow, but min cost. require each push at least -COST
            if (dis[t] >= 0) break;
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

void solve() {
    int n1,n2,m,r,b;
    cin >> n1 >> n2 >> m >> r >> b;
    string s1,s2;
    cin >> s1 >> s2;
    int S = n1+n2, T = S + 1;
    MCMF g(T+1, S, T);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--; y+=n1;
        g.add(x, y, 1, r);
        g.add(y, x, 1, b);
    }
    int cnt = 0;
    const int CAP = 2*m; 
    const int COST = 100005; 
    for (int i = 0; i < n1; i++) {
        if (s1[i] == 'R') {
            g.add(S, i, 1, -COST);
            g.add(S, i, CAP);
            cnt++;
        } else if (s1[i] == 'B') {
            g.add(i, T, 1, -COST);
            g.add(i, T, CAP);
            cnt++;
        } else {
            g.add(S, i, CAP);
            g.add(i, T, CAP);
        }
    }
    for (int i = 0; i < n2; i++) {
        int k = i + n1;
        if (s2[i] == 'B') {
            g.add(S, k, 1, -COST);
            g.add(S, k, CAP);
            cnt++;
        } else if (s2[i] == 'R') {
            g.add(k, T, 1, -COST);
            g.add(k, T, CAP);
            cnt++;
        } else {
            g.add(S, k, CAP);
            g.add(k, T, CAP);
        }
    }
    int flow,cost;
    tie(flow,cost) = g.mcmf();
    cost += cnt * COST;
    if (cost >= COST) {
        cout << -1; return;
    }
    cout << cost << "\n";
    for (int i = 0; i < m; i++) {
        if (g.e[i*4 + 1].cap) {
            cout << 'R';
        } else if (g.e[i*4 + 3].cap) {
            cout << 'B';
        } else {
            cout << 'U';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
