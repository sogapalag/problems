#include <bits/stdc++.h>

using namespace std;

const int N = 1024; 
char a[N][N];
int X[N][N];
int Y[N][N];
using pi=pair<int, int> ;

int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};
char dir[4] = {'L', 'R', 'U', 'D'};
void solve() {
    memset(a, '?', sizeof a);
    int n; cin >> n;
    queue<pi> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> X[i][j] >> Y[i][j];
            if (X[i][j] == i && Y[i][j] == j) {
                a[i][j] = 'X';
                q.emplace(i,j);
            }
        }
    }
    // multi bfs
    while (!q.empty()) {
        int i,j;
        tie(i,j) = q.front(); q.pop();
        int tx = X[i][j];
        int ty = Y[i][j];
        //cerr<<i<<' '<<j<<endl;
        for (int _ = 0; _ < 4; _++) {
            int x = i + dx[_];
            int y = j + dy[_];
            if (a[x][y] == '?' && X[x][y] == tx && Y[x][y] == ty) {
                a[x][y] = dir[_];
                q.emplace(x,y);
            }
        }
    }

    // still cannot get to X
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i][j] != -1 && a[i][j] == '?') {
                cout << "INVALID"; return;
            }
        }
    }
    // note no need some one-draw, just set dir to some nei, as long as it's -1 too.
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i][j] == -1) {
                for (int _ = 0; _ < 4; _++) {
                    int x = i + dx[_];
                    int y = j + dy[_];
                    if (X[x][y] == -1) {
                        a[i][j] = dir[_^1];
                        break;
                    }
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] == '?') {
                cout << "INVALID"; return;
            }
        }
    }

    cout << "VALID\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << a[i][j];
        }cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
