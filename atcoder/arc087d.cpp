#include <bits/stdc++.h>

using namespace std;

const int N = 8100;
const int LIM = N<<1; 
bool dp[2][2][LIM];

void solve() {
    string s; cin >> s;
    int ta[2];
    cin >> ta[0] >> ta[1];

    s += "T";
    vector<int> a[2];
    int dir = 0;
    int len = 0;
    int n = s.size();
    int i = 0;
    while (s[i]!='T') {
        len++; i++;
    }
    dp[0][0][N+len] = true;
    dp[1][0][N] = true;
    len=0;
    for (; i < n; i++) {
        if (s[i] != 'T') len++;
        else {
            if (len) a[dir].emplace_back(len);
            dir ^= 1;
            len = 0;
        }
    }

    bool res = true;
    for (int i = 0; i < 2; i++) {
        int n = a[i].size();
        int crt = 0;
        for (int j = 0; j < n; j++) {
            int nxt = crt^1;
            for (int k = 0; k < LIM; k++) {
                dp[i][nxt][k] = false;
            }
            int ds = a[i][j];
            for (int k = 0; k < LIM; k++) {
                if (k+ds < LIM) dp[i][nxt][k+ds] |= dp[i][crt][k];
                if (k-ds >= 0)  dp[i][nxt][k-ds] |= dp[i][crt][k];
            }
            crt ^= 1;
        }
        res &= dp[i][crt][N+ta[i]];
    }
    cout << (res?"Yes":"No");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
