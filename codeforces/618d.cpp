#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n,x,y;
    cin >> n >> x >> y;
    vector<vector<int>> g(n);
    vector<int> deg(n);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        deg[x]++;deg[y]++;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    // intuition. proof omit
    if (x >= y) {
        int d = *max_element(deg.begin(), deg.end());
        ll res = (n-2) * 1ll * y;
        // at least/most use one 
        res += d==n-1 ? x : y;
        cout << res;
    } else {
        ll res = 0;
        // at most use, greedy, while no vertex used >2
        function<bool(int,int)> dfs = [&](int u, int p){
            int cnt = 0;
            for (int v:g[u])if(v!=p){
                if (dfs(v,u) && cnt < 2) {
                    cnt++; res++;
                }
            }
            return cnt<2;
        };
        dfs(0,-1);
        res = res * x + (n-1-res)*y;
        cout << res;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
