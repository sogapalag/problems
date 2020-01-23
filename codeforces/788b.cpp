#include <bits/stdc++.h>

using namespace std;
using ll=long long;

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

// quick realize adj-edge can work(i.e. a tree euler tour). but if envolve loop-edge, different.
// the better thinking just apply euler-path condition, 0 or 2 odd 
void solve() {
    int n,m;
    cin >> n >> m;
    Dsu d(n);
    vector<int> deg(n);
    int loop = 0;
    vector<bool> isolated(n, true);
    int root = 0;
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        root = x;
        isolated[x] = isolated[y] = false;
        d.join(x,y);
        if (x==y) loop++;
        else deg[x]++, deg[y]++;
    }
    ll res = 0;
    int iso = 0;
    for (int x: isolated) iso+=x;

    // connect? .. visit, edge. require all edge con. not vertex
    if (d.r[d.find(root)] == n - iso){
        for (ll x: deg) res += x*(x-1)/2;
        res += loop * 1ll*(m-loop);
        res += loop *1ll* (loop-1)/2;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
