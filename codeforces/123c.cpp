#include <bits/stdc++.h>

using namespace std;
using ll=long long;
const long long INF = 0x3f3f3f3f3f3f3f3f;
const int N = 111<<1; 

ll dp[N][N];
char s[N]; int T;
ll query() {
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1;
    for (int i = 0; i < T; i++) {
        for (int j = 0; j <= i; j++) {
            if (s[i]=='?'||s[i]=='(') {
                dp[i+1][j+1] += dp[i][j];
                if (dp[i+1][j+1]>INF) dp[i+1][j+1] = INF;
            }
            if (j>0 && (s[i]=='?'||s[i]==')')) {
                dp[i+1][j-1] += dp[i][j];
                if (dp[i+1][j-1]>INF) dp[i+1][j-1] = INF;
            }
        }
    }
    return dp[T][0];
}
void solve() {
    memset(s, '?', sizeof s);
    int n,m; ll k;
    cin >> n >> m >> k;
    T = n+m - 1;
    assert(T % 2 == 0);
    vector<int> mi(T, n*m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x; cin >> x;
            mi[i+j] = min(mi[i+j], x);
        }
    }
    vector<int> id(T);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](auto& u, auto& v){
        return mi[u] < mi[v];
    });
    for (int i: id) {
        s[i] = '(';
        ll way = query();
        if (way < k) {
            k -= way;
            s[i] = ')';
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << s[i+j];
        }cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
