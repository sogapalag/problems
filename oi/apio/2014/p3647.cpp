#include <bits/stdc++.h>

using namespace std;

const int NINF = 0xc0c0c0c0; 

// key: op-2 <=> u insert v,w  s.t. u-w,w-v both blue 
// Cliam: when root at init-node, the pair-blue must be vert. i.e. no /\ shape
// but init-node unknown, if u is init-node, note, only its ancestors could have /\ shape
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

    auto maxi = [](int& x, int y){
        if (x < y) x = y;
    };

    vector<array<int,2>> dn(n), incu(n), up(n);
    // dn[0/1] all edges under u, there should be future 0/1 blue to match.
    // incu, after consider u-p
    // up[0/1] all edges above u,(u-p included), wait 0/1 blue to match.
    function<void(int,int)> dfs = [&](int u, int p){
        dn[u][1] = NINF;
        for (auto& _: g[u]) {
            int v,w;
            tie(v,w) = _;
            if (v==p) continue;
            dfs(v, u);

            incu[v][0] = max(dn[v][0], dn[v][1] + w);
            incu[v][1] = dn[v][0] + w;

            maxi(dn[u][1], max(dn[u][0] + incu[v][1], dn[u][1] + incu[v][0]));
            dn[u][0] += incu[v][0];
        }
    };
    dfs(0,-1);
    // push down
    function<void(int,int)> get = [&](int u, int p){
        int mx[2] = {NINF, NINF};
        for (auto& _: g[u]) {
            int v,w;
            tie(v,w) = _;
            if (v==p) continue;
            up[v][1] = up[v][0] = up[u][0] + (dn[u][0] - incu[v][0]);
            up[v][1] += w;
            // v-u match u-p
            maxi(up[v][0], up[u][1]+w + (dn[u][0] - incu[v][0]));
            // prep best delta
            maxi(mx[1], incu[v][1] - incu[v][0]);
            if (mx[0] < mx[1]) swap(mx[0], mx[1]);
        }
        for (auto& _: g[u]) {
            int v,w;
            tie(v,w) = _;
            if (v==p) continue;
            int best = mx[0]==incu[v][1]-incu[v][0] ? mx[1] : mx[0];
            // v-u match u-v'
            maxi(up[v][0], up[u][0] + w+best + (dn[u][0] - incu[v][0]));
        }
        // after calced, push-down
        for (auto& _: g[u]) {
            int v,w;
            tie(v,w) = _;
            if (v==p) continue;
            get(v,u);
        }
    };
    up[0][1] = NINF;
    get(0,-1);
    int res = 0;
    for (int i = 0; i < n; i++) {
        maxi(res, dn[i][0] + up[i][0]);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
