#include <bits/stdc++.h>

using namespace std;

const int N = 203; 
int dp[N][N];

// with deque we could get lower complexity?
void solve() {
    int n,K;
    cin >> n >> K;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<vector<int>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }

    function<void(int,int)> dfs = [&](int u, int p){
        dp[u][0] = a[u];
        for (int v: g[u])if(v!=p){
            dfs(v, u);
        }
        for (int v: g[u])if(v!=p){
            dp[u][0] += dp[v][K];
        }
        for (int i = 1; i <= K; i++) {
            for (int v: g[u])if(v!=p){
                int sum = dp[v][i-1]; // choose v as low depth
                for (int w: g[u])if(w!=p && w!=v){
                    sum += dp[w][max(i-1, K-i)]; // d(v,w)>K too
                }
                dp[u][i] = max(dp[u][i], sum);
            }
        }
        // suffix max
        for (int i = K; i >= 1; i--) {
            dp[u][i-1] = max(dp[u][i-1], dp[u][i]);
        }
    };
    dfs(0,-1);
    cout << dp[0][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
