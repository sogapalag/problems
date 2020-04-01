#include <bits/stdc++.h>

using namespace std;
using ll=long long;
#define fi first
#define se second
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};
const int N = 512; 
ll near[N][N];
ll d[N][N][5];
struct State {
    ll d;
    int x, y, z;
    State() {}
    State(ll _d, int _x, int _y, int _z) : d(_d), x(_x), y(_y), z(_z) {}
    bool operator<(const State& _oth) const {
        return d > _oth.d;
    }
};
void solve() {
    int n,m;
    cin >> n >> m;
    ll A,B,C;
    cin >> A >> B >> C;
    int num; cin >> num;
    vector<pair<int, int>> a(num);
    {
        memset(near, -1, sizeof near);
        queue<pair<int,int>> q;
        for (auto& p: a) {
            cin >> p.fi >> p.se;
            q.push(p);
            near[p.fi][p.se] = 0;
        }
#define in(u,v) (0<=u&&u<=n && 0<=v&&v<=m)
        // multi source bfs, prep to near pick ball
        while (!q.empty()) {
            int x,y;
            tie(x,y) = q.front(); q.pop();
            for (int _ = 0; _ < 4; _++) {
                int u = x + dx[_];
                int v = y + dy[_];
                if (in(u,v)) {
                    if (near[u][v] == -1) {
                        near[u][v] = near[x][y] + C;
                        q.emplace(u, v);
                    }
                }
            }
        }
    }

    // key: spli A*p+B to p edges, thus O(n^2) edges
    {
        int Ex, Ey;
        tie(Ex, Ey) = a.back();
        memset(d, 0x3f, sizeof d);
        priority_queue<State> pq;
        int x,y;
        tie(x,y) = a[0];
        d[x][y][4] = 0; pq.emplace(0, x, y, 4);
        while (!pq.empty()) {
            auto s = pq.top(); pq.pop();
            if (s.x==Ex && s.y==Ey) {
                cout << s.d << '\n'; return;
            }
            if (s.d > d[s.x][s.y][s.z]) continue;
            if (s.z == 4) {
                for (int _ = 0; _ < 4; _++) {
                    // ready to fly
                    if (d[s.x][s.y][_] > s.d + B) {
                        d[s.x][s.y][_] = s.d + B;
                        pq.emplace(d[s.x][s.y][_], s.x,s.y,_);
                    }
                    // walk
                    int u = s.x + dx[_];
                    int v = s.y + dy[_];
                    if (in(u,v)) {
                        if (d[u][v][4] > s.d + C) {
                            d[u][v][4] = s.d + C;
                            pq.emplace(d[u][v][4], u,v,4);
                        }
                    }
                }
            } else {
                // drop to player
                if (d[s.x][s.y][4] > s.d + near[s.x][s.y]) {
                    d[s.x][s.y][4] = s.d + near[s.x][s.y];
                    pq.emplace(d[s.x][s.y][4], s.x,s.y,4);
                }
                // keep fly
                int u = s.x + dx[s.z];
                int v = s.y + dy[s.z];
                if (in(u,v)) {
                    if (d[u][v][s.z] > s.d + A) {
                        d[u][v][s.z] = s.d + A;
                        pq.emplace(d[u][v][s.z], u,v,s.z);
                    }
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
