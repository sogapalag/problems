#include <bits/stdc++.h>

using namespace std;

struct Dsu {
    int n;
    vector<int> p;
    vector<int> r;
    
    Dsu(int _n) { n = _n; p.resize(n); r.resize(n); init(); }
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

// kruskal
void solve() {
    int n,m;
    cin >> n >> m;
    vector<pair<int, int>> e(m);
    for (int i = 0; i < m; i++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        e[i] = {x,y};
    }
    Dsu d(n);
    int cnt = 0;
    for (auto& p: e) {
        int x,y;
        tie(x,y) = p;
        x = d.find(x), y = d.find(y);
        if (x != y) {
            cnt++;
            d.join(x,y);
        }
    }
    int res = cnt + 2*(n-1-cnt);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
        cout << "\n";
    }
    fflush(stdout);
}
