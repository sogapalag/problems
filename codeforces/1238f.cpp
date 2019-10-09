#include <bits/stdc++.h>

using namespace std;


// for a good tree, root could have skew left/right
//     other node can only have one skew.
// skew def: except one son, else are leaves.
//
// dp use arm[v] trk the max skew sub
// the key idea is when u!=0, we can only consider best two in vs, why?
// since skew on parent, will equiv to a good tree with root at parent. which will calc also
void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--; y--;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    vector<int> arm(n, 1);
    int res = 0;
    function<void(int,int)> dfs = [&](int u, int p){
        int mx[2] = {};
        int son = 0;
        for (int v: g[u])if(v!=p){
            dfs(v, u);
            son++;
            if (arm[v] > mx[0]) mx[0] = arm[v];
            if (mx[0] > mx[1]) swap(mx[0], mx[1]);
        }
        if (son == 0) return;
        if (u == 0) {
            if (son == 1) {
                res = max(res, 1+mx[1]+son-1);
            } else {
                res = max(res, 1+mx[1]+mx[0]+son-2);
            }
        } else {
            if (son == 1) {
                res = max(res, 2+mx[1]+son-1);
            } else {
                res = max(res, 2+mx[1]+mx[0]+son-2);
            }
        }
        arm[u] = mx[1] + son-1 + 1;
    };
    dfs(0,-1);
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
