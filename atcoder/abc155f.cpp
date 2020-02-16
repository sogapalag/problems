#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> X(n), b(n);
    {
        vector<pair<int, int>> a(n);
        for (int i = 0; i < n; i++) {
            int x,y;
            cin >> x >> y;
            a[i] = {x,y};
        }
        sort(a.begin(), a.end());
        for (int i = 0; i < n; i++) {
            tie(X[i], b[i]) = a[i];
        }
    }
    // diff, not sum
    b.push_back(0);
    for (int i = n; i >= 1; i--) {
        b[i] ^= b[i-1];
    }
    // each op, change two pos(l,r) diff
    // we wanna final all diff 0.
    vector<vector<pair<int,int>>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int l,r;
        cin >> l >> r;
        l = lower_bound(X.begin(), X.end(), l) - X.begin();
        r = upper_bound(X.begin(), X.end(), r) - X.begin();
        if (l == r)continue;
        //cerr<<l <<','<<r<<endl;
        g[l].emplace_back(r, i);
        g[r].emplace_back(l, i);
    }
    
    vector<int> res(m);
    vector<bool> trk(n + 1);
    // one can get MST, since else edges no matter, as long as each b[v] decide i.
    function<void(int,int)> dfs = [&](int u, int p){
        trk[u] = true;
        for (auto& _: g[u]) {
            int v,i;
            tie(v,i) = _;
            if (v == p) continue;
            if (trk[v]) continue;
            dfs(v, u);
            res[i] = b[v];
            b[u] ^= res[i]; b[v] ^= res[i];
        }
    };
    for (int i = 0; i <= n; i++) {
        if (!trk[i]) {
            dfs(i, -1);
            if (b[i]) { // check root consistent
                cout << -1; return;
            }
        }
    }
    // check might no edge
    for (int i = 0; i <= n; i++) {
        if (b[i]) {
            cout << -1; return;
        }
    }
    vector<int> ans;
    for (int i = 0; i < m; i++) {
        if (res[i]) ans.push_back(i);
    }
    cout << ans.size() << "\n";
    for (auto& x: ans) {
        cout << x+1 << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
