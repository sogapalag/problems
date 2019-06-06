#include <bits/stdc++.h>

using namespace std;

void solve() {
// SNIPPETS_START graph_mat_floyd_warshall
const int INF = 0x3f3f3f3f;
const int N = 300; 

int cost[N][N];
int d[N][N];
memcpy(d, cost, sizeof cost);
int n = 300;

for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (d[i][k] < INF && d[k][j] < INF) {// for negative
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}
// SNIPPETS_END
}
