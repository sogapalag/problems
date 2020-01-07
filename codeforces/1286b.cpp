#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> pa(n), c(n);
    vector<vector<int>> g(n);
    int root;
    for (int i = 0; i < n; i++) {
        int p;
        cin >> p >> c[i];
        p--;
        if (p!=-1) {
            g[p].push_back(i);
        } else root = i;
    }
    vector<int> a(n);
    vector<int> sz(n);
    function<void(int)> dfs = [&](int u){
        for (int v:g[u]){
            dfs(v);
            sz[u] += sz[v];
        }
        if (c[u] > sz[u]) {
            cout << "NO" << endl; exit(0);
        }
        sz[u]++;
    };
    dfs(root);
    vector<bool> trk(n); // log if use gnu tree
    function<void(int)> assign = [&](int u){
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (!trk[i]) {
                if (cnt == c[u]) {
                    trk[i] = 1;
                    a[u] = i;
                    break;
                }
                cnt++;
            }
        }
        for(int v:g[u]){
            assign(v);
        }
    };
    assign(root);
    cout << "YES" << "\n";
    for(int x:a){
        cout << x+1<< ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
