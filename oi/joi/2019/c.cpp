#include <bits/stdc++.h>

using namespace std;

const int N = 411; 
int dp[N][N][N][3];
void mini(int& x, int y) {
    if (x > y) x = y;
}
// dp i, x=#c0,y=#c1, c=end color
// note each color relative order reserve, so its #inv := #different color increased in pre
void solve() {
    int n; cin >> n;
    string s; cin >> s;
    vector<int> pre[3][3];
    int cnt[3] = {};
    map<char,int> mp; mp['R']=0, mp['G']=1, mp['Y']=2;
    for (int i = 0; i < n; i++) {
        int c = mp[s[i]];
        for (int k = 0; k < 3; k++) {
            pre[c][k].push_back(cnt[k]);
        }
        cnt[c]++;
    }
    if (max({cnt[0],cnt[1],cnt[2]}) > (n+1)/2) {
        cout << "-1\n"; return;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            pre[i][j].push_back(-1e8);
            pre[i][j].push_back(-1e8);
        }
    }
    memset(dp, 0x3f, sizeof dp);
    dp[1][1][0][0] = 0;
    dp[1][0][1][1] = 0;
    dp[1][0][0][2] = 0;
    for (int i = 1; i < n; i++) {
        for (int x = 0; x <= i && x <= cnt[0]; x++) {
            for (int y = 0; y <= i-x && y <= cnt[1]; y++) {
                int z = i-x-y;
                mini(dp[i+1][x+1][y][0], dp[i][x][y][1] + max(y-pre[0][1][x], 0) + max(z-pre[0][2][x], 0));
                mini(dp[i+1][x+1][y][0], dp[i][x][y][2] + max(y-pre[0][1][x], 0) + max(z-pre[0][2][x], 0));
                mini(dp[i+1][x][y+1][1], dp[i][x][y][0] + max(x-pre[1][0][y], 0) + max(z-pre[1][2][y], 0));
                mini(dp[i+1][x][y+1][1], dp[i][x][y][2] + max(x-pre[1][0][y], 0) + max(z-pre[1][2][y], 0));
                mini(dp[i+1][x][y][2],   dp[i][x][y][0] + max(x-pre[2][0][z], 0) + max(y-pre[2][1][z], 0));
                mini(dp[i+1][x][y][2],   dp[i][x][y][1] + max(x-pre[2][0][z], 0) + max(y-pre[2][1][z], 0));
            }
        }
    }
    int res = 1e9;
    for (int c = 0; c < 3; c++) {
        mini(res, dp[n][cnt[0]][cnt[1]][c]);
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
