#include <bits/stdc++.h>

using namespace std;

const int N = 10; 
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

int key[N][N];
int d[N][N][1<<N];
int door[N][N][4];

// 网络流24题 孤岛营救问题
// layer bfs
void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    {// door
        int n; cin >> n;
        for (int _ = 0; _ < n; _++) {
            int x,y,u,v,t;
            cin >> x >> y >> u >> v >> t;
            x--,y--,u--,v--,t--;
            if (t != -1) t = 1<<t;
            for (int i:{0,1,2,3}){
                if (u==x+dx[i] && v==y+dy[i]) {
                    door[x][y][i] = t;
                    door[u][v][i^1] = t;
                }
            }
        }
    }
    {// key
        int n; cin >> n;
        for (int _ = 0; _ < n; _++) {
            int x,y,t;
            cin >> x >> y >> t;
            x--,y--,t--;
            key[x][y] |= 1<<t;
        }
    }

    // bfs
    memset(d, -1, sizeof d);
    d[0][0][0] = 0;
    queue<tuple<int,int,int>> q;
    q.emplace(0,0,0);
    while (!q.empty()) {
        int x,y,z;
        tie(x,y,z) = q.front(); q.pop();
        for (int i:{0,1,2,3}){
            int need = door[x][y][i];
            if (need == -1) continue;
            if (!need || (z&need)) {
                int u = x+dx[i];
                int v = y+dy[i];
                if (0<=u&&u<n && 0<=v&&v<m) {
                    int w = z | key[u][v];
                    if (d[u][v][w] == -1) {
                        d[u][v][w] = d[x][y][z] + 1;
                        q.emplace(u,v,w);
                    }
                }
            }
        }
    }
    int res = 1e9;
    for (int z = 0; z < 1<<k; z++) {
        int x = d[n-1][m-1][z];
        if (x != -1) res = min(res, x);
    }
    if (res > 1e8) res = -1;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
