#include <bits/stdc++.h>

using namespace std;

const int N = 222; 
int dp[N][N][N]; // has considered s[..i) t[..j), current sum[unpaired'('s]. store min length

void solve() {
    string s,t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    memset(dp, 0x3f, sizeof dp);
    dp[0][0][0] = 0;
    // =n,=m. since could process all, but remain k>0
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k < N-1; k++) {
                {
                    int ni = i<n? i + (s[i]=='(') : n;
                    int nj = j<m? j + (t[j]=='(') : m;
                    int nk = k + 1;
                    //if (i==0&&j==1&&k==1) {
                    //    cout <<'!'<< ni<<','<<nj<<','<<nk<<'\n';
                    //}
                    dp[ni][nj][nk] = min(dp[ni][nj][nk], dp[i][j][k] + 1);
                }
                //if (k<5) {
                //    cout << i<<','<<j<<','<<k<<','<<dp[i][j][k]<<'\n';
                //}
            }
            // need to downwards. separate operate from above
            // e.g. if =n,=m, remain k>0, need to fill ))..), which depend on larger k fixed
            for (int k = N-1; k >= 1; k--) {
                int ni = i<n? i + (s[i]==')') : n;
                int nj = j<m? j + (t[j]==')') : m;
                int nk = k - 1;
                dp[ni][nj][nk] = min(dp[ni][nj][nk], dp[i][j][k] + 1);
            }
        }
    }
    //for (int i = 0; i <= n; i++) {
    //    for (int j = 0; j <= m; j++) {
    //        for (int k = 0; k < 5; k++) {
    //    cerr<<i<<','<<j<<','<<k<<','<<dp[i][j][k]<<endl;

    //        }
    //    }
    //}
    int i = n, j = m;
    int k = 0;
    int x = dp[n][m][0];
    //cout << x << "\n";
    string res;
    //x = 0;
    // not, we fill greedy, but backup do not ONLY consider greedy-consume. since dp-path not support that.
    while (x > 0) {
        //cerr<<i<<','<<j<<','<<k<<','<<x<<endl;
        // don't consume neither
        if (dp[i][j][k+1] == x-1) {
            k = k+1; x--;
            //cerr<<"#1";
            res.push_back(')'); continue;
        }
        if (k>0 && dp[i][j][k-1] == x-1) {
            k = k-1; x--;
            //cerr<<"#2";
            res.push_back('('); continue;
        }
        // greedy consume both
        {
            int pi = i>0? i - (s[i-1]==')') : 0;
            int pj = j>0? j - (t[j-1]==')') : 0;
            int pk = k + 1;
            if (dp[pi][pj][pk] == x-1) {
                i = pi; j = pj; k = pk;
                //cerr<<"#3";
                res.push_back(')'); x--; continue;
            }
        }
        // greedy t
        {
            int pi = i;
            int pj = j>0? j - (t[j-1]==')') : 0;
            int pk = k + 1;
            if (dp[pi][pj][pk] == x-1) {
                i = pi; j = pj; k = pk;
                //cerr<<"#4";
                res.push_back(')'); x--; continue;
            }
        }
        // greedy s
        {
            int pi = i>0? i - (s[i-1]==')') : 0;
            int pj = j;
            int pk = k + 1;
            if (dp[pi][pj][pk] == x-1) {
                i = pi; j = pj; k = pk;
                //cerr<<"#5";
                res.push_back(')'); x--; continue;
            }
        }
        if (k > 0){
            int pi = i>0? i - (s[i-1]=='(') : 0;
            int pj = j>0? j - (t[j-1]=='(') : 0;
            int pk = k - 1;
            if (dp[pi][pj][pk] == x-1) {
                i = pi; j = pj; k = pk;
                //cerr<<"#6";
                res.push_back('('); x--; continue;
            }
        }
        if (k > 0){
            int pi = i;
            int pj = j>0? j - (t[j-1]=='(') : 0;
            int pk = k - 1;
            if (dp[pi][pj][pk] == x-1) {
                i = pi; j = pj; k = pk;
                //cerr<<"#7";
                res.push_back('('); x--; continue;
            }
        }
        if (k > 0){
            int pi = i>0? i - (s[i-1]=='(') : 0;
            int pj = j;
            int pk = k - 1;
            if (dp[pi][pj][pk] == x-1) {
                i = pi; j = pj; k = pk;
                //cerr<<"#8";
                res.push_back('('); x--; continue;
            }
        }
    }
    reverse(res.begin(), res.end());
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
