#include <bits/stdc++.h>

using namespace std;
using pi=pair<int, int> ;

const int N = 2048; 
char s[N][N];
bool trk[N][N];



void solve() {
    int n,m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> &s[i][1];
    }
    auto need = [&](int i, int j){
        if (s[i][j]!='*') return 0;
        if (s[i-1][j]=='.' && s[i][j-1]=='.' && s[i-1][j-1]=='.') return 1;
        if (s[i+1][j]=='.' && s[i][j+1]=='.' && s[i+1][j+1]=='.') return 2;
        if (s[i-1][j]=='.' && s[i][j+1]=='.' && s[i-1][j+1]=='.') return 3;
        if (s[i+1][j]=='.' && s[i][j-1]=='.' && s[i+1][j-1]=='.') return 4;
        return 0;
    };
    queue<pi> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (need(i,j)) q.emplace(i, j);
        }
    }
    while (!q.empty()) {
        int i,j;
        tie(i,j) = q.front(); q.pop();
        if (trk[i][j]) continue;
        trk[i][j] = 1;
        s[i][j] = '.';
        for (int x: {i-1,i,i+1}) {
            for (int y: {j-1,j,j+1})if(!trk[x][y] && s[x][y]=='*'){
                if (need(x,y)) q.emplace(x,y);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << s[i][j];
        }cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
