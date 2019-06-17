#include <bits/stdc++.h>

using namespace std;

const int N = 1003; 
int d[N][N][11];

struct Node {
    int u, v, k, dis;
    Node(int _u, int _v, int _k, int _dis) : u(_u), v(_v), k(_k), dis(_dis) {}
    friend bool operator < (const Node& a, const Node& b) {
        return a.dis > b.dis;
    }
};
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int a[N][N];
void solve() {
    int n, K;
    cin >> n >> K;
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        for (int j = 1; j <= n; j++) {
            a[i][j] = s[j-1] == '#';
        }
    }
    memset(d, 0x3f, sizeof d);
    d[1][1][0] = 0;
    priority_queue<Node> pq;
    pq.emplace(1, 1, 0, 0);
    while (!pq.empty()) {
        auto& tt = pq.top();
        int u = tt.u, v = tt.v, k = tt.k, dis = tt.dis;
        pq.pop();
        for (int i = 0; i < 4; i++) {
            int x = u+dx[i], y = v+dy[i];
            int kk = k + a[x][y];
            if (kk <= K && x && y && x <= n && y <= n && d[x][y][kk] > d[u][v][k] + 1) {
                d[x][y][kk] = d[u][v][k] + 1;
                pq.emplace(x, y, kk, d[x][y][kk]);
            }
        }
    }
    int res = 0x3f3f3f3f;
    for (int i = 0; i <= K; i++) {
        res = min(res, d[n][n][i]);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
