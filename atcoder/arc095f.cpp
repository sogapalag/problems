#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    vector<int> deg(n, 0);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
        deg[x]++;
        deg[y]++;
    }
    if (n <= 3) {
        for (int i = 1; i <= n; i++) {
            cout << i << ' '; return;
        }
    }
    // find diameter/body
    vector<int> d(n);
    function<void(int,int)> dfs = [&](int u,int p){
        for (int v: g[u]){
            if (v == p) continue;
            d[v] = d[u] + 1;
            dfs(v,u);
        }
    };
    d[0]=1; dfs(0,-1);
    int root = max_element(d.begin(),d.end())-d.begin();
    vector<int> pa(n,-1);
    function<void(int,int)> find = [&](int u, int p){
        for (int v:g[u]){
            if (v==p) continue;
            d[v] = d[u]+1;
            pa[v] = u;
            find(v, u);
        }
    };
    d[root]=1; find(root, -1);
    int tail = max_element(d.begin(),d.end())-d.begin();
    vector<bool> is_body(n,false);
    vector<int> des;
    {
        int v = tail;
        while (v != -1) {
            des.emplace_back(deg[v]);
            is_body[v] = true;
            v = pa[v];
        }
    }
    // is caterpillar?
    for (int i = 0; i < n; i++) {
        if (!is_body[i] && deg[i] > 1) {
            cout << -1; return;
        }
    }
    // path rev, which better
    {
        int m = des.size();
        // -- except head/tail
        for (int i = 1; i < m-1; i++) {
            des[i]--;
        }
        auto rdes = des;
        reverse(rdes.begin(), rdes.end());
        if (rdes < des) swap(rdes, des);
    }
    // shift
    vector<int> res(n);
    int pos = 0, i = 1;
    for (int x: des) {
        for (int j = 1; j < x; j++) {
            res[pos++] = i+j;
        }
        res[pos++] = i;
        i = i+x;
    }
    for (int x: res) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
