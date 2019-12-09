#include <bits/stdc++.h>

using namespace std;

const int N = 100005; 
const int B = 52; 
int dp[2][2][B]; // [0/1]: las # type-3 used or not
char s[N];

void solve() {
    int n,K,X,Y,Z;
    cin >> n >> K >> X >> Y >> Z;
    memset(s, '#', sizeof s);
    cin >> (&s[1]); s[n+1] = '#';
    memset(dp, 0xaa, sizeof dp);
    dp[0][0][0] = 0;
    int las = 0;
    int crt = 0;
    int block = -1;
    for (int i = 1; i <= n+1; i++) {
        if (s[i] == '#') {
            block++;
            if (las == i-1) {
                las = i; continue;
            }
            int nxt = crt ^ 1;
            memset(dp[nxt], 0xaa, sizeof dp[nxt]);
            for (int j = 0; j < B; j++) {
                int& x = dp[nxt][0][j];
                x = max(x, dp[crt][0][j] + (i-1-las)/2);
                x = max(x, dp[crt][1][j] + (i-2-las)/2);
            }
            if (s[i+1] != '#') {
                for (int j = 0; j < B-1; j++) {
                    int& x = dp[nxt][1][j+1];
                    x = max(x, dp[crt][0][j] + (i-2-las)/2);
                    if (i-las > 2) {
                        x = max(x, dp[crt][1][j] + (i-3-las)/2);
                    }
                }
            }
            las = i;
            crt ^= 1;
        }
    }
    int res = 0;
    for (int _ = 0; _ < 2; _++) {
        for (int j = 0; j < B; j++) {
            if (dp[crt][_][j] >= 0) {
                int y = dp[crt][_][j], z = j;
                //cout << j << ','<<y << "\n";
                int x = n - y*2-z*2 - block;

                int tmp = z*Z;
                int lim = K;
                if (X*2 > Y) {
                    tmp += min(lim, x) * X;
                    lim -= min(lim, x);
                    if (lim > 0) {
                        tmp += min(lim/2, y) * X*2;
                        y -= min(lim/2, y);
                    }
                    if ((lim&1) && y > 0 && X > Y) {
                        tmp += X;
                        y--;
                    }
                    tmp += y*Y;
                } else {
                    tmp += min(lim, x)*X;
                    tmp += y*Y;
                }
                res = max(res, tmp);
            }
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
