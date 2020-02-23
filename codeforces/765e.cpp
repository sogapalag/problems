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

    // use mid of diam as root.
    // thus any subtree except root, must return one depth. (if other root, would be possible merge uptree)
    int r,diam = 0;
    vector<int> pa(n);
    function<void(int,int,int)> dfs = [&](int u, int p, int depth){
        if (depth > diam) {
            diam = depth;
            r = u;
        } 
        pa[u]=p;
        for (int v:g[u])if(v!=p){
            dfs(v,u,depth+1);
        }
    };
    dfs(0,-1,0); diam = 0; // diam clear, otherwise, r might remain, but pa error
    dfs(r,-1,0);
    {
        int step = diam / 2;
        while (step--) {
            r = pa[r];
        }
    }
    assert(r != -1);

    auto ensure = [](bool b){
        if(!b) {
            cout << -1; exit(0);
        }
    };
    function<int(int,int,int)> match = [&](int u, int p, int depth){
        set<int> s;
        for (int v:g[u])if(v!=p){
            s.insert(match(v,u,depth+1));
        }
        if(s.empty()) return depth;
        if (u == r) {
            ensure(s.size() <= 2);
            int res = 0;
            for (auto& x: s) {
                res += x;
            }
            return res;
        } else {
            ensure(s.size() == 1);
            return *s.begin();
        }
    };
    int res = match(r,-1,0);
    while (res % 2 == 0) {
        res /= 2;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
