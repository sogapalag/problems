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
    int size(int x){
        return r[find(x)];
    }
};

void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    Dsu d(n);
    vector<set<int>> fr(n);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        d.join(x,y);
        fr[x].insert(y);
        fr[y].insert(x);
    }
    vector<int> res(n);
    for (int i = 0; i < n; i++) {
        res[i] = d.size(i) - fr[i].size() - 1;
    }
    for (int _ = 0; _ < k; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        if (fr[x].find(y) == fr[x].end() && d.check(x,y)) {
            res[x]--;
        }
        swap(x,y);
        if (fr[x].find(y) == fr[x].end() && d.check(x,y)) {
            res[x]--;
        }
    }
    for (auto& x: res) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
