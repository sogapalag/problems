#include <bits/stdc++.h>

using namespace std;

struct Dsu {
    int n;
    vector<int> p;
    
    Dsu(int _n) { n = _n; p.resize(n); init(); }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
    }
    inline int find(int x) {
        return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline bool join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        p[y] = x; return true;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
};

const int N = 303; 
int a[N][N];
const int LIM = 2e6+10; 
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

// offline each color, contribution diff
//   indep each add/del
//  add is easy to understand.
//  for del, note real diff = -(time-reveral diff)
//    i.e.  t <- t+1 (+D)  =>  t-1 -> t  (-D)
void solve() {
    memset(a, -1, sizeof a);
    int n,m,q;
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            a[i][j] = 0;
        }
    }
    int C = 1;
    vector<vector<tuple<int,int,int>>> add(LIM), del(LIM);
    for (int i = 0; i < q; i++) {
        int x,y,c;
        cin >> x >> y >> c;
        if (a[x][y] == c) continue;
        add[c].emplace_back(x,y, i);
        del[a[x][y]].emplace_back(x,y, i);
        C = a[x][y] = c;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            del[a[i][j]].emplace_back(i,j, q);
        }
    } 
    for (int i = 0; i <= C; i++) {
        reverse(del[i].begin(), del[i].end());
    }

    vector<int> diff(q + 1);
    auto f = [&](int i, int j){
        return (i-1)*m + j-1;
    };
    auto calc = [&](const auto& evs, int coeff){
        Dsu d(n*m);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                a[i][j] = 0;
            }
        }
        for (auto& _: evs) {
            int x,y,i;
            tie(x,y,i) = _;
            int delta = 1; // delta
            a[x][y] = 1;
            for (int _ = 0; _ < 4; _++) {
                int nx = x + dx[_];
                int ny = y + dy[_];
                if (a[nx][ny] == 1) {
                    delta -= d.join(f(x,y), f(nx,ny));
                }
            }
            diff[i] += delta * coeff;
        }
    };
    for (int i = 0; i <= C; i++) {
        calc(add[i], +1);
        calc(del[i], -1);
    }
    int res = 1;
    for (int i = 0; i < q; i++) {
        res += diff[i];
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
