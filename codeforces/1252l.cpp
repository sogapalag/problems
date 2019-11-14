#include <bits/stdc++.h>

using namespace std;

struct Dinic {
    using F = int;
    const static F INF = 0x3f3f3f3f; 
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
                int flow = dfs(v, min(e[i].cap, lim-tot));
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

template <typename T=int>
struct Compress {
    map<T, int> id;
    vector<T> num;

    inline int get_id(T x) {
        if (!id.count(x)) {
            id[x] = num.size();
            num.emplace_back(x);
        }
        return id[x];
    }
    inline int get_num(int i) {
        assert(0 <= i && i < num.size());
        return num[i];
    }
};

void solve() {
    int n, K;
    cin >> n >> K;
    int vnt = n;
    int S = vnt++;
    int C = vnt++;
    int T = vnt++;
    vector<vector<pair<int,int>>> g(n);
    vector<int> road(n);
    vector<vector<int>> materials(n);
    Compress<> comp;
    for (int u = 0; u < n; u++) {
        int v, m;
        cin >> v >> m;
        v--;
        g[u].emplace_back(v,u);
        g[v].emplace_back(u,u);
        road[u] = v;
        for (int _ = 0; _ < m; _++) {
            int x; cin >> x;
            materials[u].emplace_back(vnt + comp.get_id(x));
        }
    }
    vector<int> worker(K);
    for (int _ = 0; _ < K; _++) {
        int x; cin >> x;
        worker[_] = vnt + comp.get_id(x);
    }
    int N = vnt + comp.num.size();

    vector<bool> cycle(n, false);
    
    // mark cycle edge
    {vector<int> sta(n, 0); int tim = 1;
    vector<pair<int, int>> pth;
    function<bool(int,int)> dfs = [&](int u, int p){
        sta[u] = tim++;
        for (auto& _: g[u]) {
            int v,i;
            tie(v,i) = _;
            if (v == p) continue;
            if (!sta[v]) {
                pth.emplace_back(u,i);
                if (dfs(v, u)) return true;
            } else if (sta[u] > sta[v]){
                cycle[i] = true;
                while (true) {
                    int x, j;
                    tie(x, j) = pth.back(); pth.pop_back();
                    cycle[j] = true;
                    if (x == v) break;
                }
                return true;
            }
        }
        pth.pop_back();
        return false;
    };dfs(0, -1);}
    Dinic mf(N, S, T);
    // S,C -> city
    int len = 0;
    for (int i = 0; i < n; i++) {
        if (cycle[i]) {
            len++;
            mf.add(C, i, 1);
        } else {
            mf.add(S, i, 1);
        }
    }
    mf.add(S, C, len-1);
    // city -> B
    vector<int> es; // record id, to backup b could use for i?
    for (int i = 0; i < n; i++) {
        for (int b: materials[i]) {
            es.emplace_back(mf.m);
            mf.add(i, b, 1);
        }
    }
    // B -> T
    for (int b: worker) {
        mf.add(b, T, 1);
    }

    int flow = mf.flow();
    //cout << flow;
    if (flow != n-1) {
        cout << -1; return;
    }
    map<int, vector<int>> used;
    for (int _: es) {
        if (mf.e[_].cap == 0)
            used[mf.e[_].v].emplace_back(mf.e[_^1].v);
    }
    for (int b: worker) {
        if (used[b].empty()) {
            cout << "0 0\n";
        } else {
            int u = used[b].back(); used[b].pop_back();
            int v = road[u];
            cout << u+1 << ' ' << v+1 << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
