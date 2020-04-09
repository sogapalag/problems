#include <bits/stdc++.h>
#include "friend.h"

using namespace std;

// note problem ask max indepset in the spectial graph.
// let's focus the tree(generating process)
// ignore 2(which 0+1 property) first
// two are friend by a chain 011..1, (or below c-c')
// dp, in sub as long as valid
// ex, exclude the component with u by 1-edge, i.e. they're all not chosen
//
//      u
//    /0  \1
//   c  -  c' 
//
// note the c,c' are component by 1-edge, and each vertex c-c' connect too
// if u use, imply c not use, so c-c' effect can omit consider
// if u not use, let v(u) be  0110011100.. one can see valid iff no c1 use after c0 use.
//   (c use means exist vertex use in the component)
int findSample(int n, int a[], int pa[], int op[]) {
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
        g[pa[i]].push_back(i);
    }
    vector<int> dp(n), ex(n);
    function<void(int)> dfs = [&](int u){
        int x = a[u]; // use u
        int y[2] = {}; // not use u
        // y[0], some component of 0-edge sub used
        // y[1], not
        for (int v:g[u]) {
            dfs(v);
            int t = op[v];
            // x
            if (t == 0 || t == 2) {
                x += ex[v];
            } else {
                x += dp[v];
            }

            // y
            if (t == 0) {
                y[0] = max(y[0]+dp[v], y[1]+dp[v]);
                y[1] += ex[v];
            } else if (t == 1) {
                y[0] += ex[v];
                y[1] += dp[v]; //max(dp[v], ex[v]); assert>=
            } else {
                y[0] = max(y[0]+ex[v], y[1]+dp[v]); // ex[v]
                y[1] += ex[v];
            }

            // ex
            if (t == 0) {
                ex[u] += dp[v];
            } else {
                ex[u] += ex[v];
            }
        }
        dp[u] = max({x, y[0], y[1]});
        assert(dp[u] >= ex[u]);
    };
    dfs(0);
    return dp[0];
}
