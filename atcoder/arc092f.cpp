#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n), r(n);
    for (int i = 0; i < m; i++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].emplace_back(i,y);
        r[y].emplace_back(i,x);
    }
    vector<bool> trk(n, false);
    function<void(int)> dfs = [&](int u){
        trk[u] = true;
        for (auto& p: g[u]) {
            int i,v;
            tie(i,v) = p;
            if (!trk[v]) {
                dfs(v);
            }
        }
    };
    vector<bool> in_scc(m);// i.e. g:v->u
    for (int v = 0; v < n; v++) {
        fill(trk.begin(), trk.end(), 0);
        dfs(v);
        for (auto& p: r[v]) {
            int i,u;
            tie(i,u) = p;
            in_scc[i] = trk[u];
        }
    }
    vector<bool> use_extra(m);// i.e. g:u -..> v
    for (int u = 0; u < n; u++) {
        for (int _ = 0; _ < 2; _++) {
            fill(trk.begin(), trk.end(), 0);
            trk[u] = true;
            for (auto& p: g[u]) {
                int i,v;
                tie(i,v) = p;
                if (trk[v]) use_extra[i] = true; // lbro,rbro can make to v
                else dfs(v);
            }
            reverse(g[u].begin(), g[u].end());
        }
    }
    for (int i = 0; i < m; i++) {
        cout << (in_scc[i] == use_extra[i]? "same":"diff") << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
