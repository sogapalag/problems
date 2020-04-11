#include <bits/stdc++.h>

using namespace std;
using ll=long long;
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};
void solve() {
    int n,m;
    cin >> n >> m;
    ll S = 0;
    vector<vector<int>> g(n+2, vector<int>(m+2));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> g[i][j];
            S += g[i][j];
        }
    }
    vector<set<int>> R(n+1), C(m+1);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m+1; j++) {
            R[i].insert(j);
        }
    }
    for (int j = 1; j <= m; j++) {
        for (int i = 0; i <= n+1; i++) {
            C[j].insert(i);
        }
    }
    vector<pair<int, int>> a;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int p = 0, q = 0;
            for (int _ = 0; _ < 4; _++) {
                int x = i+dx[_];
                int y = j+dy[_];
                if (g[x][y] > 0) p += g[x][y], q++;
            }
            if (q>0 && q*g[i][j] < p) a.emplace_back(i, j);
        }
    }
    vector<vector<bool>> trk(n+2, vector<bool>(m+2));
    ll res = S;
    // multi bfs, since in first-place or by influ.
    while (!a.empty()) {
        for (auto& _: a) {
            int i,j;
            tie(i,j) = _;
            trk[i][j] = true;
            S -= g[i][j];
            R[i].erase(j);
            C[j].erase(i);
        }
        res += S;
        vector<pair<int, int>> candi;
        for (auto& _: a) {
            int i,j;
            tie(i,j)=_;
            int k = *R[i].lower_bound(j+1);
            if (k <= m && !trk[i][k]) {
                candi.emplace_back(i, k);
            }
            k = *--R[i].lower_bound(j);
            if (k >= 1 && !trk[i][k]) {
                candi.emplace_back(i, k);
            }
            k = *C[j].lower_bound(i+1);
            if (k <= n && !trk[k][j]) {
                candi.emplace_back(k, j);
            }
            k = *--C[j].lower_bound(i);
            if (k >= 1 && !trk[k][j]) {
                candi.emplace_back(k, j);
            }
        }
        a.clear();
        for (auto& _: candi) {
            int i,j;
            tie(i,j) = _;
            int p = 0, q = 0;
            int k = *R[i].lower_bound(j+1);
            if (k <= m && !trk[i][k]) {
                p += g[i][k], q++;
            }
            k = *--R[i].lower_bound(j);
            if (k >= 1 && !trk[i][k]) {
                p += g[i][k], q++;
            }
            k = *C[j].lower_bound(i+1);
            if (k <= n && !trk[k][j]) {
                p += g[k][j], q++;
            }
            k = *--C[j].lower_bound(i);
            if (k >= 1 && !trk[k][j]) {
                p += g[k][j], q++;
            }
            if (q>0 && q*g[i][j] < p) {
                a.emplace_back(i, j);
            }
        }
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
