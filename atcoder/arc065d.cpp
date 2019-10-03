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

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    Dsu road(n), rail(n);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        road.join(x,y);
    }
    for (int _ = 0; _ < q; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        //if (road.check(x,y))
        //    rail.join(x,y);
        rail.join(x,y);
    }
    map<pair<int, int>, int> mp;
    for (int i = 0; i < n; i++) {
        mp[{road.find(i), rail.find(i)}]++;
    }
    for (int i = 0; i < n; i++) {
        cout << mp[{road.find(i), rail.find(i)}] << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
