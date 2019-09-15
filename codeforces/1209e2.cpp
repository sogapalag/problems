#include <bits/stdc++.h>

using namespace std;

const int N = 12; 
const int M = 2000; 
int a[N][M];
int memo[N][1<<N];
int dp[N+1][1<<N];

// bitmask dp, think some subset sum proc, not max proc
void solve() {
    int n,m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    vector<int> mx(m);
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            mx[j] = max(mx[j], a[i][j]);
        }
    }
    // only at most greater n matter
    vector<int> id(m);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](auto& u, auto& v){
        return mx[u] > mx[v];
    });
    m = min(n,m);

    // memo[x][msk]: xth col, fill msk's max-sum. i.e. for (1<<n) subset, for (n) offset
    memset(memo, 0, sizeof memo);
    const int MSK = 1<<n; 
    for (int x = 0; x < m; x++) {
        int j = id[x];
        for (int ofs = 0; ofs < n; ofs++) {
            for (int msk = 0; msk < MSK; msk++) {
                int sum = 0;
                for (int i = 0; i < n; i++) {
                    if (msk & (1<<i)) {
                        sum += a[(i+ofs)%n][j];
                    }
                }
                memo[x][msk] = max(memo[x][msk], sum);
            }
        }
    }
    // for till x, x use different sub make crt msk max
    memset(dp, 0, sizeof dp);
    for (int x = 0; x < m; x++) {
        //int j = id[x];
        for (int msk = 0; msk < MSK; msk++) {
            //for (int sub = msk; sub >= 0; sub--) {
            //    sub &= msk;
            //    int sum = dp[x][msk^sub] + memo[x][sub];
            //    dp[x+1][msk] = max(dp[x+1][msk], sum);
            //}
            // not significantly fast
            dp[x+1][msk] = max(dp[x+1][msk], dp[x][msk]);//sub=0
            for (int sub = msk; sub > 0; (sub-=1)&=msk) {
                int sum = dp[x][msk^sub] + memo[x][sub];
                dp[x+1][msk] = max(dp[x+1][msk], sum);
            }
        }
    }

    int res = dp[m][MSK-1];
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
