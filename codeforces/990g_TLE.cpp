#include <bits/stdc++.h>

using namespace std;

#define __up_loop(f) \
    for (int n = f.size(), i = 1; i < n; i++)\
        for (int j = i; (j += i) < n;)
#define __dn_loop(f) \
    for (int n = f.size(), i = n-1; i >= 1; i--)\
        for (int j = i; (j += i) < n;)

template <typename T>
inline void zeta(vector<T>& f) {
    __dn_loop(f) f[j] += f[i];
}
template <typename T>
inline void mobius(vector<T>& F) {
    __up_loop(F) F[j] -= F[i];
}
template <typename T>
inline void zeta_p(vector<T>& f) {
    __up_loop(f) f[i] += f[j];
}
template <typename T>
inline void mobius_p(vector<T>& F) {
    __dn_loop(F) F[i] -= F[j];
}

const int N = 2e5+10; 
vector<int> ds[N];
void prep() {
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j+=i) {
            ds[j].push_back(i);
        }
    }
}

using ll=long long;
struct CentroidDecompositionAutomaton {
    int n;
    vector<vector<int>> g;
    vector<bool> trk;
    vector<int> sz, a, dp;
    vector<int> centroids_tour;
    vector<ll> F;
#define __limit_loop for(int v:g[u])if(!trk[v]&&v!=p)
#define __adj_loop for(int v:g[u])if(v!=p)
    CentroidDecompositionAutomaton(int _n)
        : n(_n)
        , g(n)
        , trk(n, false)
        , sz(n)
        , a(n)
        , dp(n)
        , F(N)
    {
        input();
    }
    inline void add(int u, int v) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        assert(u != v);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    void input() {
        for (auto& x: a) {
            cin >> x;
        }
        int u, v;
        for (int _ = 1; _ < n; _++) {
            cin >> u >> v;
            u--;v--; // to 0-based
            add(u, v);
        }
    }
    int SZ, CEN;
    void find_centroid(int u, int p) {
        sz[u] = 1;
        bool yes = true;
        __limit_loop {
            find_centroid(v, u);
            yes &= sz[v] <= SZ/2;
            sz[u] += sz[v];
        }
        yes &= SZ - sz[u] <= SZ/2;
        if (yes) CEN = u;
    }
    void recalc_sz(int u, int p) {
        sz[u] = 1;
        __limit_loop {
            recalc_sz(v, u);
            sz[u] += sz[v];
        }
    }
    void get_centroids_tour(int u, int p) {
        find_centroid(u, -1);
        trk[u=CEN] = true;
        centroids_tour.push_back(u);
        recalc_sz(u, -1);
        __limit_loop {
            SZ = sz[v];
            get_centroids_tour(v, u);
        }
    }

    void run() {
        centroids_tour.reserve(n);
        SZ = n; get_centroids_tour(0,-1);
        fill(trk.begin(), trk.end(), false);
        for (int u: centroids_tour) {
            solve(u);
            trk[u] = true;
        }
        mobius_p(F);
        for (int i = 1; i <= 200000; i++) {
            if (F[i]) {
                cout << i << ' ' << F[i] << "\n";
            }
        }
    }
    ll c2(ll n){ return n*(n-1)/2; }
    // Caution: use __limit_loop to dfs
    void solve(int u) {
        for (int d: ds[a[u]]) {
            function<void(int,int)> dfs = [&](int u, int p){
                dp[u] = 0;
                if (a[u] % d != 0) return; // can early
                else dp[u]++;
                __limit_loop {
                    dfs(v,u);
                    dp[u] += dp[v];
                }
            };
            dfs(u,-1);
            F[d] += c2(dp[u]) + 1;
            for (int v:g[u])if(!trk[v]){
                F[d] -= c2(dp[v]);
            }
        }
    }
#undef __limit_loop
#undef __adj_loop
};

// O(nlogn K), K=160, TLE. need constant-optim?
void solve() {
    prep();
    int n; cin >> n;
    CentroidDecompositionAutomaton cda(n);
    cda.run();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
