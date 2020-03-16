#include <bits/stdc++.h>

using namespace std;
using ll=long long;

ll sq(ll n){ return n*n; }
ll c2(ll n){ return n*(n-1)/2; }
ll c3(ll n){ return n*(n-1)*(n-2)/6; }


// BCC(点双连通分量) https://www.cnblogs.com/PinkRabbit/p/Introduction-to-Round-Square-Tree.html
// tree: for each BC create square node, origin-nodes belong connect it.
// for this problem, let R-node weight -1, S-node weight n(BC sz).
// then for path(a, c), #b = sum of path on tree.
//  then consider b's contribution
void solve() {
    int n,m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    vector<int> sta(n,-1), low(n);
    int tim = 0;
    int N;
    vector<int> tour;
    vector<vector<int>> tr(2 * n);
    int BC = n;
    vector<int> a(2 * n); // weight
    auto add = [&](int bc, int x){
        tr[bc].push_back(x);
        tr[x].push_back(bc);
        ++a[bc];
    };
    function<void(int)> tarjan = [&](int u){
        low[u] = sta[u] = tim++;
        tour.push_back(u);
        for (int v:g[u]){
            if (sta[v] != -1) low[u] = min(low[u], sta[v]); // at least u-p edge, o-o cut too
            else {
                tarjan(v);
                low[u] = min(low[u], low[v]);
                if (sta[u] == low[v]) { // u is cut-point
                    int x;
                    do {
                        x = tour.back(); tour.pop_back();
                        add(BC, x);
                    } while (x != v);
                    add(BC, u); // u can be in other BC, not pop yet
                    BC++;
                }
            }
        }
    };
    ll res = 0;
    vector<int> sz(2 * n);
    function<void(int,int)> dfs = [&](int u, int p){
        sz[u] = (u < n);
        for (int v:tr[u])if(v!=p){
            dfs(v, u);
            res += 2ll*a[u] * sz[u]*sz[v];
            sz[u] += sz[v];
        }
        // uptree
        res += 2ll*a[u] * sz[u]*(N-sz[u]);
    };
    fill(a.begin(), a.begin()+n, -1);
    for (int i = 0; i < n; i++) {
        if (sta[i] == -1) {
            tim = 0;
            tour.clear();
            tarjan(i);
            N = tim;
            dfs(i, -1);
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
