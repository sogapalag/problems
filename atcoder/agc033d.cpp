#include <bits/stdc++.h>

using namespace std;

const int N = 188; 

int dpR[2][N][N][N];
int dpD[2][N][N][N];

// when range [l, r), has property P~notP, want last P.
// when return l-1, means not found.
template <typename T>
inline
T bs_last(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = (l+r)/2;
        if (f(mid)) {
            l = mid + 1;
        }else {
            r = mid;
        }
    }
    return r-1;
}

// dpR(ight),D(own), [x][y][u/v] store top-left at(x,y), bottom-right (u/v), maximum coord. reach crt complex
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n+1, vector<int>(m+1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c; cin >> c;
            if (c == '#') a[i][j] = 1;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            a[i][j] += a[i][j-1];
        }
    }
    for (int j = 1; j <= m; j++) {
        for (int i = 1; i <= n; i++) {
            a[i][j] += a[i-1][j];
        }
    }
    auto sum = [&](int x, int y, int u, int v){
        return a[u][v] - a[x-1][v] - a[u][y-1] + a[x-1][y-1];
    };
    auto mono = [&](int x, int y, int u, int v){
        int tmp = sum(x, y, u, v);
        return tmp == 0 || tmp == (u-x+1)*(v-y+1);
    };
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= m; y++) {
            // init with those complex = 0
            for (int u = x; u <= n; u++) {
                dpR[0][x][y][u] = bs_last<int>(y, m+1, [&](int v){
                        return mono(x, y, u, v);
                        });                
            }
            for (int v = y; v <= m; v++) {
                dpD[0][x][y][v] = bs_last<int>(x, n+1, [&](int u){
                        return mono(x, y, u, v);
                        });
            }
        }
    }
    for (int res = 0; ; res++) {
        if (dpR[0][1][1][n] == m) {
            cout << res; break;
        }
        for (int x = 1; x <= n; x++) {
            for (int y = 1; y <= m; y++) {
                // [] span:= []|[]
                for (int u = x; u <= n; u++) {
                    int v = dpR[0][x][y][u];
                    if (v < m) v = dpR[0][x][v+1][u];
                    dpR[1][x][y][u] = v;
                }
                for (int v = y; v <= m; v++) {
                    int u = dpD[0][x][y][v];
                    if (u < n) u = dpD[0][u+1][y][v];
                    dpD[1][x][y][v] = u;
                }
            }
        }
        for (int x = 1; x <= n; x++) {
            for (int y = 1; y <= m; y++) {
                // ck another dim may span.
                for (int u = x; u <= n; u++) {
                    int v = dpR[1][x][y][u];
                    while (v < m && dpD[1][x][y][v+1] >= u) {
                        v++;
                    }
                    dpR[0][x][y][u] = v;
                }
                for (int v = y; v <= m; v++) {
                    int u = dpD[1][x][y][v];
                    while (u < n && dpR[1][x][y][u+1] >= v) {
                        u++;
                    }
                    dpD[0][x][y][v] = u;
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
