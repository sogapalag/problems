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

int eid[111][111];

// 网络流24题 航空路线问题
// key: (i->i+n) indicate use city-i once. and come&go <=> two goes(0 -> n-1)
void solve() {
    int n,m;
    cin >> n >> m;
    unordered_map<string, int> mp;
    vector<string> cities(n);
    for (int i = 0; i < n; i++) {
        cin >> cities[i];
        mp[cities[i]] = i;
    }
    int S = 0, T = 2*n-1;
    MCMF g(2*n, S, T);
    for (int i = 0; i < n; i++) {
        if (i == 0 || i == n-1) g.add(i, i+n, 2);
        else g.add(i, i+n, 1, -1);
    }
    for (int _ = 0; _ < m; _++) {
        string s,t;
        cin >> s >> t;
        int x = mp[s], y = mp[t];
        if (x > y) swap(x, y);
        eid[x][y] = g.e.size();
        if (x==0 && y==n-1) g.add(x+n, y, 2); // this flight can twice
        else g.add(x+n, y, 1);
    }
    int flow, cost;
    tie(flow, cost) = g.mcmf();
    if (flow < 2) {
        cout << "No Solution!"; return;
    }
    cout << -cost+2 << "\n";
    if (cost == 0) {
        for (int i:{0,n-1,0}){
            cout << cities[i] << "\n";
        }
        return;
    }
    vector<int> left(n,-1), right(n,-1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            int x = eid[j][i];
            if (x && g.e[x^1].cap) {
                right[left[i] = j] = i;
            }
        }
    }
    vector<vector<int>> path;
    for (int i = 1; i < n; i++) {
        if (left[i] == 0) {
            vector<int> a;
            a.push_back(0);
            int x = i;
            while (x != -1) {
                a.push_back(x);
                x = right[x];
            }
            assert(a.back() == n-1);
            path.push_back(a);
        }
    }
    assert(path.size() == 2);
    for (int i:path[0]) {
        cout << cities[i] << "\n";
    }
    auto& a = path[1];
    a.pop_back();
    reverse(a.begin(), a.end());
    for (int i:a) {
        cout << cities[i] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
