#include <bits/stdc++.h>

using namespace std;

template <typename M>
struct SegTree {
    using Op = function<M(const M&, const M&)>;
    M ID; // monoid identity
    Op op; // associative operation
    int N; // 2^lg space, for non-commutative
    vector<M> a;
    
    SegTree(int n, M leaf_default, M _ID, Op _op) : ID(_ID), op(_op) {
        init_space(n);
        fill(a.begin() + N, a.begin() + N + n, leaf_default);
        build();
    }
    SegTree(const vector<M> leaves, M _ID, Op _op) : ID(_ID), op(_op) {
        int n = leaves.size();
        init_space(n);
        copy(leaves.begin(), leaves.end(), a.begin() + N);
        build();
    }
    void init_space(int n) {
        N = 1; while (N < n) N<<=1;
        a.assign(N<<1, ID);
    }
    inline void pull(int i) { a[i] = op(a[i<<1], a[i<<1|1]); }
    void build() { for (int i = N-1; i >= 1; i--) pull(i); }

    void assign(int p, M val) {
        assert(0 <= p && p < N);
        for (a[p += N] = val; p >>= 1;) pull(p);
    }
    void update(int l, int r, M val) {
        assert(0 <= l && r <= N);
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) a[l] = op(a[l], val), l++;
            if (r & 1) --r, a[r] = op(a[r], val);
        }
    }
    void push_all() {
        for (int i = 1; i < N; i++) {
            a[i<<1] = min(a[i<<1], a[i]);
            a[i<<1|1] = min(a[i<<1|1], a[i]);
        }
    }
    //M query(int l, int r) const {
    //    assert(0 <= l && r <= N);
    //    M resl(ID), resr(ID);
    //    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    //        if (l & 1) resl = op(resl, a[l++]);
    //        if (r & 1) resr = op(a[--r], resr);
    //    }
    //    return op(resl, resr);
    //}
    //M query_point(int p) const { 
    //    assert(0 <= p && p < N);
    //    return a[p + N];
    //}
    //M query_all() const { return a[1]; }
};
using ll=long long;
struct Graph {
    //using CT = int; static const CT INF = 0x3f3f3f3f;
    using CT = long long; static const CT INF = 0x3f3f3f3f3f3f3f3f;
    struct Edge {
        int u, v;
        CT cost;
        Edge(int _u, int _v, CT _cost) : u(_u), v(_v), cost(_cost) {}
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
    Graph(int _n, int _m, bool _di=false) : n(_n), pe(n, -1) {
        assert(n >= 1);
        g.resize(n);
        e.reserve(_m);
        m = 0;
        set_di(_di);
        input(_m);
    }
    void set_di(bool _di) {
        is_digraph = _di;
    }
    inline void add(int u, int v, CT cost=1) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        if (is_digraph) {
            //outdeg[u]++; indeg[v]++;
            g[u].emplace_back(m);

        } else {
            //deg[u]++; deg[v]++;
            g[u].emplace_back(m);
            g[v].emplace_back(m);
        }
        e.emplace_back(u, v, cost);
        m++;
    }
    void input(int _m) {
        int u, v; int c;
        for (int i = 0; i < _m; i++) {
            scanf("%d%d%d", &u,&v,&c);
            //cin >> u >> v >> c;
            u--; v--; // input 1-based
            add(u, v, c);
        }
    }

    // if multi-source, add dummy SOURCE
    // single source shortest path
    vector<CT> dijkstra(int s) {
        fill(pe.begin(), pe.end(), -1);
        vector<bool> trk(n, false);
        vector<CT> d(n, INF);
        d[s] = 0;
        using pi=pair<CT,int>;
        priority_queue<pi, vector<pi>, greater<pi>> pq;
        pq.push({0, s});
        while (!pq.empty()) {
            CT dis; int u;
            tie(dis, u) = pq.top(); pq.pop();
            if (trk[u])
                continue;
            trk[u] = true;
            for (int i: g[u]) {
                int v = e[i].u ^ e[i].v ^ u;
                if (d[v] > d[u] + e[i].cost) {
                    d[v] = d[u] + e[i].cost;
                    pq.push({d[v], v});
                    // new
                    pe[v] = i;
                }
            }
        }
        return d;
    }

    vector<int> find_leaving0(vector<CT>& d) {
        vector<int> id(n);
        iota(id.begin(), id.end(), 0);
        sort(id.begin(), id.end(), [&](auto& u, auto& v){
            return d[u] < d[v];
        });
        vector<int> dp(n, 1e7); dp[0] = 0;
        for (int u:id) {
            for (int i:g[u]) {
                int v = e[i].u^e[i].v^u;
                if (d[u]+e[i].cost == d[v]) {
                    if (ord[i] >= 0) dp[v] = min(dp[v], ord[i]+1);
                    else dp[v] = min(dp[v], dp[u]);
                }
            }
        }
        return dp;
    }
    vector<int> find_leaving1(vector<CT>& d, int k) {
        vector<int> id(n);
        iota(id.begin(), id.end(), 0);
        sort(id.begin(), id.end(), [&](auto& u, auto& v){
            return d[u] < d[v];
        });
        vector<int> dp(n, -1); dp[n-1] = k;
        for (int u:id) {
            for (int i:g[u]) {
                int v = e[i].u^e[i].v^u;
                if (d[u]+e[i].cost == d[v]) {
                    if (ord[i] >= 0) dp[v] = max(dp[v], ord[i]);
                    else dp[v] = max(dp[v], dp[u]);
                }
            }
        }
        return dp;
    }

    vector<int> pe;
    vector<int> ord;
//#define LOCAL
    void process(int q) {
        clock_t test_begin = clock();
#ifdef LOCAL
clock_t begin_t = clock();  
#endif
        auto d0 = dijkstra(0);
        auto d1 = dijkstra(n-1);
        if (clock() - test_begin > 1800) {
            cout << "find?"; assert(false);
        }
        if (0 && n==150000) {
            // dij:101,  ;  638ms?
            cout <<"dij:"<< clock()-test_begin<<endl; exit(0);
        }
#ifdef LOCAL
clock_t now_t = clock();  
cerr << "dijk: ";
cerr << (double)(now_t-begin_t)/CLOCKS_PER_SEC <<endl;
begin_t = now_t;
#endif
        vector<int> path; path.reserve(m);
        ord.assign(m, -1);
        {
            int x = 0;
            while (x != n-1) {
                int i = pe[x];
                ord[i] = path.size();
                path.push_back(i);
                x ^= e[i].u ^ e[i].v;
                //if (clock() - test_begin > 1800) {
                //    cout << "loop"; assert(false);
                //}
            }
        }
        int k = path.size();
        auto dp0 = find_leaving0(d0);
        auto dp1 = find_leaving1(d1, k);
        if (0 && n == 150000) {
            // find:126   ; 654 ms
            cout << "find:" << clock()-test_begin << endl; exit(0);
        }
        if (clock() - test_begin > 1800) {
            cout << "find?"; assert(false);
        }
#ifdef LOCAL
now_t = clock();  
cerr << "find: ";
cerr << (double)(now_t-begin_t)/CLOCKS_PER_SEC <<endl;
begin_t = now_t;
#endif
        SegTree<ll> rmi(k, 1e18, 1e18, [](ll u, ll v){ return min(u,v); });
        for (int i = 0; i < m; i++) {
            if (ord[i] == -1) {
                int u = e[i].u, v = e[i].v;
                rmi.update(dp0[u], dp1[v], d0[u]+d1[v] + e[i].cost);
                swap(u,v);
                rmi.update(dp0[u], dp1[v], d0[u]+d1[v] + e[i].cost);
            }
        }
        rmi.push_all();
        if (0 && n == 150000) {
            // seg:208  ;592ms
            cout << "seg:" << clock()-test_begin << endl; exit(0);
        }
#ifdef LOCAL
now_t = clock();  
cerr << "rmi: ";
cerr << (double)(now_t-begin_t)/CLOCKS_PER_SEC <<endl;
begin_t = now_t;
#endif
        //ll* best = &(rmi.a[rmi.N]);
        vector<ll> best = vector<ll>(rmi.a.begin() + rmi.N, rmi.a.begin()+rmi.N + k);
        if (clock() - test_begin > 1800) {
            cout << "before query"<<endl; exit(0);
        }
        while (q--) {
            int i,w;
            //cin >> i >> w;i--;
            scanf("%d%d", &i,&w); i--;
            int u = e[i].u, v = e[i].v;
            ll res = min(d0[u]+d1[v]+w, d0[v]+d1[u]+w);
            if (ord[i] == -1) {
                res = min(res, d1[0]);
            } else {
                res = min(res, best[ord[i]]);
            }
            if (clock() - test_begin > 1800) {
                cout << "remain:" << q << endl; exit(0);
            }
            //cout << res << '\n';
            printf("%lld\n", res);
        }
    }
};

// next time, never use cin,cout.  >2000ms.TLE replace scanf,printf  500ms.AC.   fuck!!
//
// let main path be shortest path 0->n-1.
// solution: note the trick part is that, if modify e of path, and increase it.
//                   the candidate can be some path won't cross e.
//   the key insight is to find dp[u], the earlest leaving(main path) time for shortest 0-u
//    with these, we can get non-main-path u-v contribute.
//      i.e. dp[u] indicate shortest 0->u must use some prefix of main-path. simmilarily dp1 suffix
//   then with segtree, we get leaves: the shortest path without an e of main-path.
void solve() {
    int n,m,q;
    //cin >> n >> m >> q;
    scanf("%d%d%d", &n,&m,&q);
    Graph g(n,m);
    g.process(q);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
