#include <bits/stdc++.h>

using namespace std;

const int N = 3010; 
int n,m;
int a[N];
vector<int> g[N];
using ll=long long ;
using pi =pair<int, ll>;

inline pi operator+(const pi& u, const pi& v) {
    return pi(u.first+v.first, u.second+v.second);
}
int sz[N];
pi dp[N][N], tmp[N];
// [u][cuts], {#par>0, sum for future}
void dfs(int u, int p) {
    sz[u] = 0;
    dp[u][0] = {0, a[u]};
    for (int v: g[u])if(v!=p){
        dfs(v,u);
        for (int i = 0; i <= sz[u]; i++) {
            tmp[i] = dp[u][i];
        }
        for (int i = 0; i <= sz[u]+sz[v]; i++) {
            dp[u][i] = {-1,0};
        }
        for (int i = 0; i <= sz[u]; i++) {
            for (int j = 0; j <= sz[v]; j++) {
                dp[u][i+j] = max(dp[u][i+j], tmp[i] + dp[v][j]);
            }
        }
        sz[u] += sz[v];
    }
    sz[u]++;
    dp[u][sz[u]] = {-1,0};// leaf could (0,-x)

    if (u == 0) {
        for (int i = sz[u]-1; i >= 0; i--) {
            dp[u][i+1] = pi(dp[u][i].first + (dp[u][i].second>0), 0); // must cut u-p
        }
        return;
    }

    for (int i = sz[u]-1; i >= 0; i--) {
        dp[u][i+1] = max(dp[u][i+1], pi(dp[u][i].first + (dp[u][i].second>0), 0)); // if cut u-p, 
    }

}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        g[i].clear();
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i] = x - a[i];
    }
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    dfs(0,-1);
    cout << dp[0][m].first << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
