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

void solve() {
    int n,m;
    cin >> n >> m;
    vector<pair<int, int>> e(m);
    for (int i = 0; i < m; i++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        e[i]= {x,y};
    }
    int cnt = 0;
    for (int i = 0; i < m; i++) {
        Dsu d(n);
        for (int j = 0; j < m; j++) {
            if (j!=i) {
                int x,y;
                tie(x,y) = e[j];
                d.join(x,y);
            }
        }
        int x,y;
        tie(x,y) = e[i];
        if (!d.check(x,y)) cnt++;
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
