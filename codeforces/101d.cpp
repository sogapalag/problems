#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<vector<pair<int,int>>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x,y,z;
        cin >> x >> y >> z;
        x--;y--;
        g[x].emplace_back(y,z);
        g[y].emplace_back(x,z);
    }
    vector<double> once(n), sum(n), sz(n);
    function<void(int,int)> dfs = [&](int u,int p){
        vector<pair<double,double>> a;
        for (auto& _: g[u]) {
            int v,w;
            tie(v,w) = _;
            if (v == p) continue;
            dfs(v,u);
            once[u] += once[v] + w * sz[v];
            a.emplace_back(sum[v] + w, sz[v]);
            sz[u] += sz[v];
        }
        ++sz[u];
        // when consider pair contribution.
        //  cost 2*sum0*sz1
        sort(a.begin(), a.end(), [&](auto& u, auto& v){
            return u.first*v.second < u.second*v.first;
        });
        double pref = 0;
        for (auto& _: a) {
            double x,y;
            tie(x,y) = _;
            once[u] += 2 * pref * y;
            pref += x;
        }
        sum[u] = pref;
    };
    dfs(0,-1);
    cout << fixed << setprecision(10) << once[0]/(n-1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
