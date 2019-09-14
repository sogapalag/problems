#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
const int N = 10; 

int cost[N][N];

void solve() {
    int H, W;
    cin >> H >> W;
    int n=10;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[j][i]; // tran
        }
    }
    auto dijkstra = [&](int s){
        vector<int> d(n, INF);
        vector<bool> trk(n, false);
        d[s] = 0;
        while (true) {
            int mindis = INF;
            int u = -1;
            for (int i = 0; i < n; i++) {
                if (!trk[i] && d[i] < mindis) {
                    u = i; mindis = d[i];
                }
            }
            if (!~u) break;
            trk[u] = true;
            for (int v = 0; v < n; v++) {
                if (!trk[v] && d[v] > d[u] + cost[u][v]) {
                    d[v] = d[u] + cost[u][v];
                }
            }
        }
        return d;
    };
    auto d = dijkstra(1);
    vector<int> cnt(10);
    for (int _ = 0; _ < H; _++) {
        for (int _ = 0; _ < W; _++) {
            int x; cin >> x;
            if (x!=-1)cnt[x]++;
        }
    }
    int res = 0;
    for (int i = 0; i < n; i++) {
        res += cnt[i] * d[i];
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
