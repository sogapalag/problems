#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vector<int> res(n);
    vector<int> c[3];
    for (int i = 1; i <= n; i++) {
        c[i%3].push_back(i);
    }
    vector<vector<int>> a(2);
    function<void(int,int,int)> dfs = [&](int u, int p,int depth){
        a[depth&1].push_back(u);
        for (int v:g[u])if(v!=p){
            dfs(v,u,depth+1);
        }
    };
    dfs(0,-1,0);
    if (a[0].size() > a[1].size()) swap(a[0], a[1]);

    auto take = [](vector<int>& v){
        int x = v.back(); v.pop_back();
        return x;
    };

    if (a[0].size() <= c[0].size()) {
        // a[0] all use 3.6...
        while (a[0].size()) {
            int u = a[0].back(); a[0].pop_back();
            int x = c[0].back(); c[0].pop_back();
            res[u] = x;
        }
        for (int i:{0,1,2}) {
            while (c[i].size()) {
                int u = take(a[1]);
                int x = take(c[i]);
                res[u] = x;
            }
        }
    } else {
        // put 1.. 2.. into each
        assert(c[1].size() <= a[0].size());
        assert(c[2].size() <= a[1].size());
        while (c[1].size()) {
            res[take(a[0])] = take(c[1]);
        }
        while (c[2].size()) {
            res[take(a[1])] = take(c[2]);
        }
        for (int i:{0,1}) {
            while (a[i].size()) {
                res[take(a[i])] = take(c[0]);
            }
        }
    }

    for (auto& x: res) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
