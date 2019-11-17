#include <bits/stdc++.h>

using namespace std;

struct Dsu {
    int n;
    vector<int> p;
    vector<int> r;
    vector<int> mx;
    
    Dsu(int _n) { n = _n; p.resize(n); r.resize(n); mx.resize(n); init(); }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
            r[i] = 1;
            mx[i] = i;
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
        mx[x] = max(mx[x], mx[y]);
        return true;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
    inline int get_mxr(int x) {
        return mx[find(x)];
    }
};

// note valid form [1..] [..] [..] ..[..n]
void solve() {
    int n,m;
    cin >> n >> m;
    Dsu d(n);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        d.join(x,y);
    }
    int cnt = 0;
    int i = 0, r;
    while (i < n) {
        while (i < (r = d.get_mxr(i))) {
            cnt += d.join(++i, r);
        }
        ++i;
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
