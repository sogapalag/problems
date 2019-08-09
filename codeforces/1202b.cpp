#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int cnt[10][10];
int dp[10][10][10][10]; // i->j with x-y machine min-step(insertion)
int res[10][10];

void pre() {
    memset(dp, INF, sizeof dp);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for (int x = 0; x < 10; x++) {
                for (int y = 0; y < 10; y++) {
                    for (int s = 0; s < 10; s++) {
                        for (int t = 0; t < 10; t++) {
                            if ((s+t)>0 && (i + x*s + y*t - j ) %10 == 0) {
                                int& k = dp[i][j][x][y];
                                k = min(k, s+t-1);
                            }
                        }
                    }
                }
            }
        }
    }
}

void solve() {
    string s; cin >> s;
    memset(cnt, 0, sizeof cnt);
    for (int i = 0; i+1 < (int)s.size(); i++) {
        cnt[s[i]-'0'][s[i+1]-'0']++;
    }
    pre();
    auto calc = [&](int x, int y){
        int sum = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (cnt[i][j] == 0) continue;
                if (dp[i][j][x][y] == INF) return -1;
                sum += dp[i][j][x][y] * cnt[i][j];
            }
        }
        return sum;
    };
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j <= i; j++) {
            res[i][j] = res[j][i] = calc(i, j);
        }
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << res[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
