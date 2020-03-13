#include <bits/stdc++.h>

using namespace std;

int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};
int d[111][111][11];
int oil[111][111];
using State = tuple<int,int,int,int>;
struct comp {
    bool operator()(const State& a, const State& b)const {
        return get<0>(a) > get<0>(b);
    }
};


bool trk[111][111][11]; // can omit, checked dis > d
// 网络流24题 汽车加油行驶问题
// layer dijkstra
void solve() {
    int n,K,A,B,C;
    cin >> n >> K >> A >> B >> C;
    C += A;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> oil[i][j];
        }
    }
    int co[4] = {0,B,0,B};
    
    memset(d, 0x3f, sizeof d);
    priority_queue<State,vector<State>,comp> pq;
    d[0][0][K] = 0;
    pq.emplace(0,0,0,K);
    while (!pq.empty()) {
        int dis,i,j,k;
        tie(dis,i,j,k) = pq.top(); pq.pop();
        if (dis > d[i][j][k]) continue;
        if (trk[i][j][k]) continue;
        trk[i][j][k] = true;
        for (int _:{0,1,2,3}) {
            int x = i + dx[_];
            int y = j + dy[_];
            if (0<=x&&x<n && 0<=y&&y<n) {
                if (oil[x][y]) { // x,y....not i,j... why always miswriten!!!!
                    int z = K; // full
                    if (!trk[x][y][z] && d[x][y][z] > dis + co[_] + A) {
                        d[x][y][z] = dis + co[_] + A;
                        pq.emplace(d[x][y][z], x,y,z);
                    }
                } else {
                    {
                        int z = k-1;
                        if (!trk[x][y][z] && d[x][y][z] > dis + co[_]) {
                            d[x][y][z] = dis + co[_];
                            if(z)pq.emplace(d[x][y][z], x,y,z);
                        }
                    }
                    {// new oil
                        int z = K;
                        if (!trk[x][y][z] && d[x][y][z] > dis + co[_] + C) {
                            d[x][y][z] = dis + co[_] + C;
                            pq.emplace(d[x][y][z], x,y,z);
                        }
                    }
                }
            }
        }
    }
    int res = 2e9;
    for (int k = 0; k <= K; k++) {
        res = min(res, d[n-1][n-1][k]);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
