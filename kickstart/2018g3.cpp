#include <bits/stdc++.h>

using namespace std;

int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};
const int V = 100000; 
const int N = 103; 
int a[N][N];
bool trk[N][N];
#define in(i,j) (0<=i&&i<n && 0<=j&&j<m)
#define iswall(i,j) (a[i][j]==-V)
#define istrap(i,j) (a[i][j] < 0 && a[i][j] > -V)

// note optim is always trav component >=0, then decide which trap next
// O(nm2^k) prep offline vol[msk]:=energy after pass those traps 
// O(k2^k) decide dp[msk]=vol[msk] or -1, i.e. msk can actually achievable
void solve() {
    int n,m,e,sx,sy,tx,ty;
    cin >> n >> m >> e >> sx >> sy >> tx >> ty;
    --sx;--sy;--tx;--ty;
    vector<pair<int, int>> trap;
    map<pair<int,int>,int> kth;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            if (istrap(i,j)) {
                pair<int,int> p{i,j};
                kth[p] = trap.size();
                trap.push_back(p);
            }
        }
    }
    const int K = trap.size();
    const int MSK = 1<<K;
    vector<int> vol(MSK);
    vector<bool> ok(MSK);
    // prep
    for (int msk = 0; msk < MSK; msk++) {
        memset(trk, 0, sizeof trk);
        int& res = vol[msk];
        queue<pair<int,int>> q;
        q.emplace(sx, sy);
        res += e;
        trk[sx][sy] = true;
        while (!q.empty()) {
            int i,j;
            tie(i,j) = q.front(); q.pop();
            for (int _ = 0; _ < 4; _++) {
                int x = i+dx[_];
                int y = j+dy[_];
                if (in(x,y) && !trk[x][y] && !iswall(x,y)) {
                    if (!istrap(x,y) || (msk>>kth[{x,y}]&1) ) {
                        trk[x][y] = true;
                        res += a[x][y];
                        q.emplace(x,y);
                    }
                }
            }
        }
        ok[msk] = trk[tx][ty];
    }
    vector<int> dp(MSK, -1); dp[0] = vol[0];
    for (int msk = 0; msk < MSK; msk++) if(dp[msk] >= 0){
        for (int i = 0; i < K; i++) {
            if (msk>>i&1) continue;
            int x,y;
            tie(x,y) = trap[i];
            // need not check trap connected, since this would be same compo but worse vol
            if (dp[msk]+a[x][y] >= 0) {
                dp[msk^1<<i] = vol[msk^1<<i];
            }
        }
    }
    int res = -1;
    for (int msk = 0; msk < MSK; msk++) {
        if (ok[msk]) res = max(res, dp[msk]);
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
