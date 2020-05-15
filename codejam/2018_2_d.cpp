#include <bits/stdc++.h>

using namespace std;

struct Dsu {
    int n;
    vector<int> p;
    vector<int> r;
    
    Dsu(int _n) : n(_n)
        , p(n)
        , r(n)
    {
        init();
    }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
            r[i] = 1;
        }
    }
    inline int find(int x) {
        return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline bool join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (r[x] < r[y]) swap(x, y);
        p[y] = x; r[x] += r[y];
        return true;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
};
int a[22][22];
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};
// note one need occur infinitely has a pattern
// x|y
// -.-
// u|v   i.e. par.into 4 part, each sats. color
// so iter patter 2^4, iter cut, n^2.
//   find max component.
void solve() {
    int n,m;
    cin >> n >> m;
    vector<string> s(n);
    for (auto& x: s) cin >> x;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i][j] = s[i][j]=='B';
        }
    }

    int res = 0;
    // 001  no 01 actually
    // 100     10
    // need ensure check
    vector<bool> trk(16);
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            int pat = 0;
            pat |= a[i][j];
            pat |= a[i][j-1]<<1;
            pat |= a[i-1][j]<<2;
            pat |= a[i-1][j-1]<<3;
            trk[pat] = true;
        }
    }
    for (int pat = 0; pat < 16; pat++) {
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) if(trk[pat] || (i==0||i==n) || (j==0||j==m)){
                // =0,=n not trk for pat B|W or B
                Dsu d(n*m);
#define in(x,y) (0<=x&&x<n && 0<=y&&y<m)
#define sat(x,y) (a[x][y] == (pat>>((x<i)*2+(y<j))&1))
                for (int x = 0; x < n; x++) {
                    for (int y = 0; y < m; y++) if(sat(x,y)){
                        for (int _ = 0; _ < 4; _++) {
                            int u = x + dx[_];
                            int v = y + dy[_];
                            if (in(u,v) && sat(u,v)) {
                                d.join(x*m+y, u*m+v);
                            }
                        }
                    }
                }
                int mx = *max_element(d.r.begin(), d.r.end());
                res = max(res, mx);
            }
        }
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
