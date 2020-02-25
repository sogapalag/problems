#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n; cin >> n;
    vector<vector<pair<int,int>>> g(n);
    vector<pair<int, int>> es(n-1);
    for (int _ = 1; _ < n; _++) {
        int x,y,z;
        cin >> x >> y >> z;
        x--;y--;
        g[x].emplace_back(y, z);
        g[y].emplace_back(x, z);
        es[_-1] = {x,y};
    }

    vector<ll> dn(n), up(n);
    vector<int> pa(n), sz(n);
    vector<int> tour; tour.reserve(n);
    function<void(int,int)> dfs = [&](int u, int p){
        tour.push_back(u);
        pa[u] = p;
        dn[u] = 0;
        sz[u] = 0;
        for (auto [v,w]: g[u])if(v!=p){
            dfs(v, u);
            dn[u] += dn[v] + sz[v] * 1ll * w;
            sz[u] += sz[v];
        }
        ++sz[u];
    };

    // note dn[]+up[] is sum of dist from .
    // we find max delta of which, since only that matter
    // fix erased-edge, two-side consideration is independent,
    auto calc = [&](int u, int v){
        tour.clear(); dfs(u, v);
        up[u] = 0;
        int n = sz[u];
        for (int u: tour) {
            for (auto [v,w]: g[u])if(v!=pa[u]){
                up[v] = up[u] + dn[u] - (dn[v] + sz[v]*1ll*w);
                up[v] += (n-sz[v])*1ll*w;
            }
        }
        int x = *min_element(tour.begin(), tour.end(), [&](int u, int v){
                return dn[u]+up[u] < dn[v]+up[v];
                });
        return dn[u]+up[u] - dn[x]-up[x];
    };
    ll best = 0;
    for (auto [u,v]: es) {
        ll x = calc(u,v), su = sz[u];
        ll y = calc(v,u), sv = sz[v];
        best = max(best, x * sv + y * su);
    }

    ll base = 0;
    tour.clear(); dfs(0,-1);
    for (int u: tour) {
        for (auto [v,w]: g[u])if(v!=pa[u]){
            base += sz[v]*1ll*w*(n-sz[v]);
        }
    }
    //cerr<<base<<endl;
    
    cout << base - best;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
