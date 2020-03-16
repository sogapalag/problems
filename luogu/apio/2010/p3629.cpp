#include <bits/stdc++.h>

using namespace std;

struct E {
    int u, v, w;
    E() {}
    E(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
};

// https://www.cnblogs.com/water-mi/p/9365911.html
void solve() {
    int n,k;
    cin >> n >> k;
    vector<E> e(n-1);
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; i++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        e[i] = {x, y, 1};
        g[x].push_back(i);
        g[y].push_back(i);
    }

    int diam = -1, rt = -1;
    vector<int> pe(n);
    function<void(int,int)> dfs = [&](int u, int depth){
        if (depth > diam) {
            diam = depth;
            rt = u;
        }
        for (int i:g[u])if(i!=pe[u]){
            int v = e[i].u^e[i].v^u;
            pe[v] = i;
            dfs(v,depth+1);
        }
    };
    auto take = [&](int r){
        fill(pe.begin(), pe.end(), -1);
        diam = -1, rt = -1;
        dfs(r, 0);
    };
    take(0); take(rt);
    int res = 2*(n-1) - (diam-1);

    if (k == 2) {
        // mark diameter weight -1
        int x = rt;
        while (pe[x] != -1) {
            int i = pe[x];
            e[i].w = -1;
            x = e[i].u^e[i].v^x;
        }
        // calc new diameter
        vector<int> arm(n);
        int mx = 0;
        fill(pe.begin(), pe.end(), -1);
        function<void(int)> calc = [&](int u){
            for (int i:g[u])if(i!=pe[u]){
                int v = e[i].u^e[i].v^u;
                pe[v] = i;
                calc(v);
                mx = max(mx, arm[u] + arm[v] + e[i].w);
                arm[u] = max(arm[u], arm[v] + e[i].w);
            }
        };
        calc(0);
        res -= mx-1;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
