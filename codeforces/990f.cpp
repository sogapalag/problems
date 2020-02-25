#include <bits/stdc++.h>

using namespace std;


// it's trivial valid iff sum=0. then fill any MST
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    int sum = 0;
    for (auto& x: a) {
        cin >> x;
        sum += x;
    }
    if (sum != 0) {
        cout << "Impossible"; return;
    }
    int m; cin >> m;
    vector<vector<pair<int,int>>> g(n);
    for (int i = 1; i <= m; i++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].emplace_back(y, i);
        g[y].emplace_back(x, -i);
    }

    vector<bool> trk(n);
    vector<int> res(m);
    function<void(int)> dfs = [&](int u){
        trk[u] = true;
        for (auto [v,i]:g[u])if(!trk[v]){
            dfs(v);
            int f = a[v] * (i>0?1:-1);
            res[abs(i)-1] = f; 
            a[u] += a[v];
        }
    };
    dfs(0);
    cout << "Possible\n";
    for (auto& x: res) {
        cout << x << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
