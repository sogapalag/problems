#include <bits/stdc++.h>

using namespace std;

char s[55][55];
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

void solve() {
    int n,m;
    cin >> n >> m;
    memset(s, '.', sizeof s);
    for (int i = 1; i <= n; i++) {
        cin >> (s[i]+1);
    }
    bool valid = true;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i][j]=='.') continue;
            bool adj = false;
            for (int k = 0; k < 4; k++) {
                adj |= s[i+dx[k]][j+dy[k]] == '#';
            }
            valid &= adj;
        }
    }
    cout << (valid? "Yes":"No");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
