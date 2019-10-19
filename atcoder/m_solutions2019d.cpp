#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    vector<int> a(n);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end());

    int sum = 0;
    for (int i = 0; i < n-1; i++) {
        sum += a[i];
    }
    // keep min as leaf
    vector<int> res(n);
    int i = 0;
    function<void(int,int)> dfs = [&](int u, int p){
        for (int v: g[u])if(v!=p){
            dfs(v,u);
        }
        res[u] = a[i++];
    };
    dfs(0,-1);

    cout << sum << "\n";
    for (auto& x: res) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
