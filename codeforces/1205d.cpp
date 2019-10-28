#include <bits/stdc++.h>

using namespace std;

// for tree use
struct Graph {
    int n, m;
    vector<vector<int>> g;
    bool is_digraph;
    Graph(int _n) : n(_n), m(0) {
        assert(n >= 1);
        g.resize(n);
        set_di(false);
    }
    Graph(int _n, int _m, bool _di=false) : n(_n), m(0) {
        assert(n >= 1);
        assert(1ll*n*(n-1)/2 >= m);
        g.resize(n);
        set_di(_di);
        input(_m);
    }
    inline void add(int u, int v) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        assert(u != v);
        g[u].emplace_back(v);
        if (!is_digraph)
            g[v].emplace_back(u);
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
    void set_di(bool _di) {
        pa = vector<int>(n, -1);
        sz = vector<int> (n, 1);
        trk = vector<bool> (n, false);
        is_digraph = _di;
    }
    
    vector<int> pa;
    vector<int> sz;
    vector<bool> trk;
    void dfs(int u) {
        trk[u] = true;
        for (int v: g[u]) if(!trk[v]){
            pa[v] = u;
            dfs(v);
            sz[u] += sz[v];
        }
    }
    vector<int> centroids(){
        dfs(0);
        vector<int> cds;
        for (int u = 0; u < n; u++) {
            bool yes = true;
            for (int v: g[u]) {
                if (v!=pa[u]) yes &= sz[v] <= n/2;
            }
            yes &= n-sz[u] <= n/2;
            if (yes) cds.emplace_back(u);
        }
        assert(cds.size() <= 2);
        return cds;
    }

    int root;
    vector<bool> co;
    vector<int> d;
    int coeff;
    int ant = 1, bnt = 1;
    // [a],   (coeff=a+1)*[b]
    void info(int u){
        trk[u] = true;
        for (int v: g[u])if(!trk[v]){
            if (u!=root) co[v] = co[u];
            if (co[v]) {
                d[v] = ant++;
                int cost = d[v] - d[u];
                cout << u+1 << ' ' << v+1 << ' ' << cost << "\n";
            } else {
                d[v] = bnt++;
                int cost = d[v] - d[u];
                cout << u+1 << ' ' << v+1 << ' ' << cost*coeff << "\n";
            }
            info(v);
        }
    }
    void run() {
        root = centroids()[0];
        sz.assign(n, 1);
        fill(trk.begin(), trk.end(), false);
        dfs(root);
        vector<pair<int, int>> son;
        for (int v: g[root]) {
            son.emplace_back(sz[v], v);
        }
        sort(son.begin(), son.end());
        int lim = (n-1)/3;
        co.assign(n, 0);
        // we don't need merge like as editorial
        // just note lemma, must pre/suf both >lim, proof omit
        for (int i = 0, sum = 0; i < (int)son.size(); i++) {
            int x,v;
            tie(x,v) = son[i];
            sum += x; co[v] = 1;
            // sz cmp is not necessary, but add then we can ensure no edge-case
            if (i+2 == (int)son.size() || sum > lim) {
                coeff = sum+1; break;
            }       
        }
        fill(trk.begin(), trk.end(), false);
        d.assign(n, 0);
        info(root);
    }
};

void solve() {
    int n; cin >> n;
    Graph g(n, n-1);
    if (n == 1) return;
    if (n == 2) {
        cout << "1 2 1"; return;
    }
    g.run();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
