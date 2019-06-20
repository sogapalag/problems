#include <bits/stdc++.h>

using namespace std;

int cnt[1<<9];   // friends compressed
int sat[1<<9];   // #friends, by a msk conver
int id[1<<9][2]; // for exactly 2 using, store best two
int cost[1<<9][2];

// only 1<<9 items. ^2 choosing.
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int msk = 0;
        int f; cin >> f;
        for (int _ = 0; _ < f; _++) {
            int j; cin >> j;
            msk |= 1 << (j-1);
        }
        cnt[msk]++;
    }
    memset(sat, 0, sizeof sat);
    for (int msk = 1; msk < (1<<9); msk++) {
        for (int x = 1; x < (1<<9); x++) {
            if ((x&msk) == x)
                sat[msk] += cnt[x];
        }
    }

    const int INF = 0x3f3f3f3f;
    memset(id, 0, sizeof id);
    memset(cost, INF, sizeof cost);
    for (int i = 1; i <= m; i++) {
        int co; cin >> co;
        int f; cin >> f;
        int msk = 0;
        for (int _ = 0; _ < f; _++) {
            int j; cin >> j;
            msk |= 1 << (j-1);
        }
        if (co < cost[msk][1]) {
            cost[msk][1] = co;
            id[msk][1] = i;
        }
        if (cost[msk][1] < cost[msk][0]) {
            swap(cost[msk][1], cost[msk][0]);
            swap(id[msk][1], id[msk][0]);
        }
    }

    int rs = 0, rc = 2*INF;
    int u, v;
    for (int i = 1; i < (1<<9); i++) {
        for (int x = 0; x < 2; x++) {
            for (int j = 1; j < (1<<9); j++) {
                for (int y = 0; y < 2; y++) {
                    if ((i!=j || x!=y) && id[i][x] && id[j][y]) {
                        if (sat[i|j] > rs) {
                            rs = sat[i|j];
                            rc = cost[i][x] + cost[j][y];
                            u = id[i][x];
                            v = id[j][y];
                        } else if (sat[i|j] == rs) {
                            int t = cost[i][x] + cost[j][y];
                            if (t < rc) {
                                rc = t;
                                u = id[i][x];
                                v = id[j][y];
                            }
                        }
                    }
                }
            }
        }
    }
    cout << u << ' ' << v;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
