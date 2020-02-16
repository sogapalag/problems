#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
template <typename T=int>
struct Fenwick2d {
    int n, m;
    vector<vector<T>> g;

    Fenwick2d(int _n, int _m) : n(_n), m(_m), g(n+1, vector<T>(m+1, INF)) {}
    inline void add(int x, int y, T val) {
        history.emplace_back(x, y);
        for (; x <= n; x += (x&-x)) {
            for (int j = y; j <= m; j += (j&-j)) {
                //g[x][j] += val;
                g[x][j] = min(g[x][j], val);
            }
        }
    }
    // 1-based [1,1..x,y] <=> 0-based [0,0..x,y)
    inline T query(int x, int y) {
        T sum = INF;
        for (; x > 0; x -= (x&-x)) {
            for (int j = y; j > 0; j -= (j&-j)) {
                //sum += g[x][j];
                sum = min(sum, g[x][j]);
            }
        }
        return sum;
    }
    vector<pair<int, int>> history;
    void reset() {
        while (!history.empty()) {
            int x,y;
            tie(x,y) = history.back(); history.pop_back();
            for (; x <= n; x += (x&-x)) {
                for (int j = y; j <= m; j += (j&-j)) {
                    //g[x][j] += val;
                    g[x][j] = INF;
                }
            }
        }
    }
    // 1-based (l..r] <=> 0-based [l..r)
    //inline T query(int xl, int yl, int xr, int yr) {
    //    return query(xr, yr) - query(xl, yr) - (query(xr, yl) - query(xl, yl));
    //}
};

int cx[4] = {-1, -1, 1, 1};
int cy[4] = {-1, 1, -1, 1};

const int N = 303; 
int dp[N][N];

// a easy method, is nm (nm)^0.5, split case cnt[v]*cnt[v+1] > nm?, dicide dp or bfs
// below just spilt, 4 case of corner, 2d rmi, O(nm log(nm))
void solve() {
    int n,m,p;
    cin >> n >> m >> p;
    vector<vector<pair<int,int>>> layer(p+1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int x; cin >> x;
            layer[x].emplace_back(i, j);
        }
    }
    vector<Fenwick2d<int>> rmi;
    memset(dp, INF, sizeof dp);
    for (int k: {0,1,2,3}) {
        rmi.emplace_back(n, m);
        int x = (k&2) ? n : 1;
        int y = (k&1) ? m : 1;
        rmi[k].add(x,y, cx[k] + cy[k]);
    }
    for (int _ = 1; _ <= p; _++) {
        for (auto& __: layer[_]) {
            int i,j;
            tie(i,j) = __;
            int& res = dp[i][j];
            for (int k: {0,1,2,3}) {
                int tmp = i * cx[k^3] + j * cy[k^3];
                // pref or suff
                int x = (k&2) ? n - i + 1 : i;
                int y = (k&1) ? m - j + 1 : j;
                res = min(res, tmp + rmi[k].query(x, y));
            }
        }
        // mannul reset, Warnning, memset=>O(pnm)
        for (int k: {0,1,2,3}) {
            rmi[k].reset();
        }
        for (auto& __: layer[_]) {
            int i,j;
            tie(i,j) = __;
            for (int k: {0,1,2,3}) {
                int tmp = i * cx[k] + j * cy[k];
                int x = (k&2) ? n - i + 1: i;
                int y = (k&1) ? m - j + 1: j;
                rmi[k].add(x, y, tmp + dp[i][j]);
            }
        }
    }
    int x,y;
    tie(x,y) = layer[p][0];
    cout << dp[x][y];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
