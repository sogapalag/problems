#include <bits/stdc++.h>
#include "friend.h"

using namespace std;
const int N = 100005; 
int f[N];
// ioi official solution
// https://ioinformatics.org/page/ioi-2014/40
// dp/f, use/not u, use imply c=neib(u) all not, we can ignore their relation
// 0,1,2 decide u(dp/f), v(dp/f) contribute which part
//
//    u
//   /  \?
//  c -? v
int findSample(int n, int dp[], int pa[], int op[]) {
    for (int i = n-1; i > 0; i--) {
        int u = pa[i];
        if (op[i] == 0) {
            dp[u] += f[i];
            f[u] += max(dp[i], f[i]);
        } else if (op[i] == 1) {
            dp[u] = max(max(dp[i],f[i])+dp[u], dp[i]+f[u]);
            f[u] += f[i];
        } else {
            dp[u] = max(dp[u]+f[i], dp[i]+f[u]);
            f[u] += f[i];
        }
    }
    return max(dp[0], f[0]);
}
