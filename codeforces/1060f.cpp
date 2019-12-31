#include <bits/stdc++.h>

using namespace std;
const int N = 52; 
double fac[N];
void prep() {
    fac[0]=fac[1]=1;
    for (int i = 2; i < N; i++) {
        fac[i] = fac[i-1]*i;
    }
}
double c(int n,int k) {return fac[n]/fac[k]/fac[n-k];}
double dp[N][N], convo[N], f[N];
// [u][i]: when there're i edges on subtree of u. after doing, remain u is root
// note when the time i edges, (u) not nessary u. it means that time the new root would keep to the end
vector<int> g[N];
int sz[N];
void dfs(int u,int p){
    sz[u] = 1;
    dp[u][0] = 1;
    for (int v: g[u])if(v!=p){
        dfs(v,u);
        for (int i = 0; i <= sz[v]; i++) {// has i after (u,p)
            f[i] = 0;
            for (int j = 0; j < sz[v]; j++) { // has j after (u,v)
                // implies (u,v) would occur early than [v][j]
                // so (u,v) must choose u. then remain is like subtree on v
                if (j<i) f[i] += 0.5 * dp[v][j]; 
                // Caution: [v][i] not j, since we iter the event j after(u,v). it's I_j contribute.
                // but the contribution is i. as there must be hit the moment i.
                else f[i] += dp[v][i]; // implies (u,v) already gone before (u,p), so no matter
            }
        }
        for (int i = 0; i < sz[u]; i++) {
            for (int j = 0; j <= sz[v]; j++) {
                convo[i+j] += dp[u][i] * f[j] * c(i+j,i) * c(sz[u]+sz[v]-i-j-1, sz[v]-j);
            }
        }
        sz[u] += sz[v];
        for (int i = 0; i < sz[u]; i++) {
            dp[u][i] = convo[i]; convo[i] = 0;
        }
    }
}
void solve() {
    prep();
    int n; cin >> n;
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    cout << fixed << setprecision(10);
    for (int i = 0; i < n; i++) {
        dfs(i,-1);
        double res = dp[i][n-1] / fac[n-1];
        cout << res << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
