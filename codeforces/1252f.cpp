#include <bits/stdc++.h>

using namespace std;

struct Sieve {
    int sz;
    vector<bool> is;
    vector<int> prime;
    Sieve(int n = 45000):sz(n) {
        prime.reserve(n/6);
        is.assign(n+1, true);
        is[0] = is[1] = false;
        for (int p = 2; (int64_t)p*p <= n; p++) {
            if (is[p]) {
                for (int i = p*p; i <= n; i += p) {
                    is[i] = false;
                }
            }
        }
        for (int i = 2; i <= n; i++) {
            if (is[i])
                prime.emplace_back(i);
        }
    }
}s(1e6);

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

    uint64_t _hash(int u) {
        trk[u] = true;
        uint64_t sum = 1;
        for (int v: g[u]) if(!trk[v]){
            sum += _hash(v) * s.prime[sz[v]];
            sz[u] += sz[v];
        }
        return sum;
    }
    uint64_t get_rooted_hash(int r) {
        fill(trk.begin(), trk.end(), false);
        fill(sz.begin(), sz.end(), 1);
        return _hash(r);
    }
    uint64_t get_unrooted_hash() {
        uint64_t res = 0;
        for (int r: centroids()) {
            res = max(res, get_rooted_hash(r));
        }
        return res;
    }
};

// https://logic.pdmi.ras.ru/~smal/files/smal_jass08.pdf
// https://oi-wiki.org/graph/tree-hash/#method-ii
// AHU algorithm, tree hash, centroids
void solve() {
    int n; cin >> n;
    Graph g(n, n-1);
    for (int r: g.centroids()) {
        if (g.g[r].size() < 2) continue; // n>=3 unnecessary
        int las = -1; // sz
        uint64_t pre = 0; // hsh
        for (int v: g.g[r]) {
            int sz = v == g.pa[r]? n - g.sz[r] : g.sz[v];
            if (las == -1) las = sz;
            else if (las != sz) {
                las = -2; break;
            }

            // bulid subtree, or use original graph, but impl painful
            Graph sg(sz);
            int cnt = 0;
            function<int(int, int)> dfs = [&](int u, int p){
                int id = cnt++;
                for (int v: g.g[u]) if(v!=p){
                    sg.add(id, dfs(v,u));
                }
                return id;
            };
            dfs(v, r);
            auto hsh = sg.get_unrooted_hash();
            if (pre == 0) pre = hsh;
            else if (pre != hsh) {
                pre = 0; break;
            }
        }
        if (las < 0 || pre == 0) continue;
        cout << g.g[r].size(); return;
    }
    cout << -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
