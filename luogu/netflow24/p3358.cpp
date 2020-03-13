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

// 网络流24题 最长k可重区间集问题
// after compress, let i[) repre each seg.
// key: at most k intersect <=> split into k sets, each are disjoint segments. - - - - 
void solve() {
    int n,k;
    cin >> n >> k;
    vector<int> Xs;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        a[i] = {x,y};
        Xs.push_back(x);
        Xs.push_back(y);
    }
    sort(Xs.begin(), Xs.end());
    Xs.erase(unique(Xs.begin(), Xs.end()), Xs.end());
    int m = Xs.size();
    auto pos = [&](int x){
        return lower_bound(Xs.begin(), Xs.end(), x) - Xs.begin();
    };
    int S = m, T = m + 1;
    MCMF g(T+1, S, T);
    g.add(S, 0, k);
    g.add(m-1, T, k);
    for (int i = 0; i < m-1; i++) {
        g.add(i, i+1, k);
    }
    for (auto& _: a) {
        int x,y;
        tie(x,y) = _;
        int d = y-x;
        x = pos(x);
        y = pos(y);
        g.add(x, y, 1, -d);
    }
    auto res = - g.mcmf().second;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
