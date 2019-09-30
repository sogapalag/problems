#include <bits/stdc++.h>

using namespace std;

int L;

struct Graph {
    struct Edge {
        int u, v;
        int cost;
        Edge(int _u, int _v, int _cost) : u(_u), v(_v), cost(_cost) {}
    };
    int n, m;
    bool is_digraph;
    vector<vector<int>> g;
    vector<Edge> e;

    Graph(int _n) : n(_n), m(0) {
        assert(n >= 1);
        g.resize(n);
        set_di(false);
    }
    Graph(int _n, int _m, bool _di=false) : n(_n) {
        assert(n >= 1);
        g.resize(n);
        e.reserve(_m);
        m = 0;
        set_di(_di);
        input(_m);
    }
    void set_di(bool _di) {
        pos = vector<int>(n, 0);
        is_digraph = _di;
        deg = vector<int> (n, 0);
    }
    vector<int> deg;
    inline void add(int u, int v, int cost=1) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        if (is_digraph) {
            //outdeg[u]++; indeg[v]++;
            g[u].emplace_back(m);

        } else {
            deg[u]++; deg[v]++;
            g[u].emplace_back(m);
            g[v].emplace_back(m);
        }
        e.emplace_back(u, v, cost);
        m++;
    }
    void input(int _m) {
        int u, v;
        for (int i = 0; i < _m; i++) {
            cin >> u >> v;
            u--; v--; // input 1-based
            add(u, v);
        }
    }
    vector<int> pos;
    vector<int> pa;
    vector<int> d;
    vector<bool> trk;
    void dfs(int u) {
        trk[u] = true;
        for (; pos[u] < (int)g[u].size(); pos[u]++) {
            int i = g[u][pos[u]];
            int v = e[i].u ^ e[i].v ^ u;
            // rule
            if (trk[v]) continue;
            pa[v] = u; d[v] = 1 + d[u];
            dfs(v);
        }
    }
    // for undirected tree
    vector<int> get_diameter() {
        pa.assign(n, -1);
        d.assign(n, 0);
        trk.assign(n, false);
        d[0] = 1; pa[0] = -1; dfs(0);
        int root = max_element(d.begin(), d.end()) - d.begin();
        fill(pos.begin(), pos.end(), 0);
        fill(trk.begin(), trk.end(), false);
        d[root] = 1; pa[root] = -1; dfs(root);
        int tail = max_element(d.begin(), d.end()) - d.begin();
        int num = d[tail];
        vector<int> pth(num);
        for (int i = num-1, x=tail; i >= 0; i--) {
            assert(x != -1);
            pth[i] = x;
            x = pa[x];
        }
        assert(pth[0] == root);
        return pth;
    }

    int tolerance;
    int error;
    int full(int u, int p) {
        vector<int> ch;
        for (; pos[u] < (int)g[u].size(); pos[u]++) {
            int i = g[u][pos[u]];
            int v = e[i].u ^ e[i].v ^ u;
            if (v == p) continue;
            ch.emplace_back(full(v, u));
        }
        if (ch.empty()) return 0;
        if (ch.size()==1) {
            if (tolerance>0 && ch[0]==0) {
                error = u;
                tolerance--;
                return 1;
            }
            else return -1;
        }
        if (ch.size()==2) {
            if (ch[0]==-1 || ch[1]==-1) return -1;
            if (ch[0]!=ch[1]) return -1;
            return ch[0] + 1;
        }
        if (ch.size()==3) {
            if (tolerance <= 0) return -1;
            error = u;
            tolerance--;
            sort(ch.begin(), ch.end());
            if (ch[0]!=ch[1]) return -1;
            if (ch[1]+1 != ch[2]) return -1;
            return ch[2] + 1;
        }
        return -1;
    }
    
    void run() {
        auto pth = get_diameter();
        if (pth.size()%2==0) {
            fill(pos.begin(), pos.end(), 0);
            tolerance = 0;
            int r[2] = {pth[pth.size()/2 - 1],pth[pth.size()/2]};
            if (full(r[0], r[1]) == L-2 && full(r[1], r[0]) == L-2) {
                if (r[0] > r[1]) swap(r[0], r[1]);
                cout << "2\n";
                cout << (r[0]+1) << ' ' << (r[1]+1);
            }else cout << 0;
        } else {
            fill(pos.begin(), pos.end(), 0);
            int r = pth[pth.size()/2];
            tolerance = 1;
            if (full(r, -1) == L-1) {
                cout << "1\n";
                cout << (error+1);
            }else cout << 0;
        }
    }
};

void solve() {
    cin >> L;
    int n = (1<<L)-2;
    Graph g(n,n-1);

    g.run();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
