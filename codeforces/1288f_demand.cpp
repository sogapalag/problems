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

void solve() {
    int n1,n2,m,r,b;
    cin >> n1 >> n2 >> m >> r >> b;
    string s1,s2;
    cin >> s1 >> s2;
    int L = n1+n2, R = L + 1;
    int S = R+1, T = S+1;
    MCMF g(T+1, S, T);
    vector<int> deg(S), demand(S);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--; y+=n1;
        deg[x]++;deg[y]++;
        demand[x]++; demand[y]--;
        g.add(x, y, 1, r);
        g.add(y, x, 1, b);
    }
    auto gg = [](){
        cout << -1; exit(0);
    };
    for (int i = 0; i < n1; i++) {
        if (s1[i] != 'U' && deg[i] == 0) gg();
        if (s1[i] == 'R') {
            g.add(L, i, deg[i] - 1);
            // L->i d+1, force (d+1-d)>=1 not directly into T, i.e. red
            demand[i] -= deg[i]+1;
            demand[L] += deg[i]+1; 
        } else if (s1[i] == 'B') {
            g.add(L, i, deg[i] - 1); // (d-(d-1))>=1, not directly from L, i.e. blue
        } else {
            g.add(L, i, deg[i]<<1);
        }
    }
    for (int i = 0; i < n2; i++) {
        int k = i + n1;
        if (s2[i] != 'U' && deg[k] == 0) gg();
        if (s2[i] == 'B') {
            g.add(k, R, deg[k] - 1); // (d-(d-1))>=1, not into R, i.e. blue
        } else if (s2[i] == 'R') {
            g.add(k, R, deg[k] - 1);
            // k->R d+1, force (d+1-d)>=1 not directly from S, i.e. red
            demand[k] += deg[k] + 1;
            demand[R] -= deg[k] + 1;
        } else {
            g.add(k, R, deg[k]<<1);
        }
    }
    // feasible
    g.add(R, L);
    int sum = 0;
    for (int i = 0; i < S; i++) {
        if (demand[i] > 0) {
            sum += demand[i];
            g.add(i, T, demand[i]);
        }
        if (demand[i] < 0) {
            g.add(S, i,-demand[i]);
        }
    }
    int flow,cost;
    tie(flow,cost) = g.mcmf();
    if (flow < sum) gg();
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
