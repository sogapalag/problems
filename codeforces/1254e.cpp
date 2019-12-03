#include <bits/stdc++.h>

using namespace std;

void ensure(bool b) {
    if (!b) {
        cout << 0 << endl; exit(0);
    }
}

// consider each u, and its adj-edge relative order. unique determine configuration
// since each edge will be considered in two ends' group. so create 2*n-2
// below notation, u and its i:u->adj
void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    vector<int> e(2*n-2);
    for (int i = 0; i < n-1; i++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].emplace_back(i<<1); e[i<<1] = y;
        g[y].emplace_back(i<<1|1); e[i<<1|1] = x;
    }

    vector<int> dep(n), pa(n,-1);
    function<void(int,int)> dfs = [&](int u, int p){
        for (int i: g[u])if ((i^p)!=1){
            int v = e[i];
            dep[v] = dep[u] + 1;
            pa[v] = i;
            dfs(v, i);
        }
    };
    dfs(0,-1);
    auto get_path = [&](int u, int v){
        vector<int> left, right;
        while (u != v) {
            if (dep[u] > dep[v]) {
                left.push_back(pa[u]^1);
                u = e[pa[u]^1];
            } else {
                right.push_back(pa[v]);
                v = e[pa[v]^1];
            }
        }
        reverse(right.begin(), right.end());
        for (auto& x: right) {
            left.push_back(x);
        }
        return left;
    };

    int total_diff = 0;
    const int HEAD = -2, TAIL = -3;
    vector<int> S(n,-1), T(n,-1), pre(2*n-2, -1), nxt(2*n-2, -1);
    // build conditions for each path
    auto limit_path = [&](int u, int v){
        auto p = get_path(u,v);
        int len = p.size();
        total_diff += len;
        // since each swap += 2
        ensure(total_diff <= 2*n-2);
        int i;
        // i must be S[u]
        i = p[0]; ensure(S[u] == -1 && pre[i] == -1); pre[i] = HEAD; S[u] = i;
        // i must be T[v]
        i = p.back()^1; ensure(T[v] == -1 && nxt[i] == -1); nxt[i] = TAIL; T[v] = i;
        // i -> j
        for (int _ = 0, j; _+1 < len; _++) {
            i = p[_], j = p[_+1];
            u = e[i]; i ^= 1;
            ensure(nxt[i] == -1 && pre[j] == -1);
            nxt[i] = j; pre[j] = i;
        }
    };

    for (int v = 0; v < n; v++) {
        int u; cin >> u; u--;
        if (u == -1) continue;
        ensure(u != v);
        limit_path(u, v);
    }

    long long res = 1;
    const long long MOD = 1e9+7; 
    vector<bool> trk(2*n-2, false);
    for (int u = 0; u < n; u++) {
        int cnt = 0; // chains
        int vis = 0; // #edges
        if (S[u] != -1) {
            int i = S[u]; trk[i] = true; vis++;
            while (nxt[i] >= 0) {
                i = nxt[i];
                ensure(!trk[i]); trk[i] = true; vis++;
            }
            // the chain must contain all
            if (T[u] == i) {
                ensure(vis == g[u].size());
            }
            cnt++;
        }
        // visit other non-HEAD chain 
        for (int i: g[u])if(pre[i]==-1){
            trk[i] = true; vis++;
            while (nxt[i] >= 0) {
                i = nxt[i];
                ensure(!trk[i]); trk[i] = true; vis++;
            }
            cnt++;
        }
        // must visit all, ensure no cycle
        ensure(vis == g[u].size());
        // freedom-dim --
        if (S[u]!=-1) cnt--;
        if (T[u]!=-1) cnt--;
        for (int i = 1; i <= cnt; i++) {
            (res *= i) %= MOD;
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
