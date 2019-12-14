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

// ignore incident to a,b edges. merge all
// check which compo is inter
void solve() {
    int n,m,a,b;
    cin >> n >> m >> a >> b;
    a--;b--;
    if (a>b)swap(a,b);
    Dsu d(n);
    vector<vector<int>> g(n);
    vector<pair<int, int>> es(m);
    for (int i = 0; i < m; i++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
        es[i] = {x,y};
        if (x!=a&&x!=b && y!=a&&y!=b) {
            d.join(x,y);
        }
    }
    set<int> sa,sb;
    for (int x: g[a]) {
        if (x!=b) {
            sa.insert(d.find(x));
        }
    }
    set<int> inter;
    for (int x: g[b]) {
        if (x!=a) {
            int s = d.find(x);
            if (sa.find(s)!=sa.end()) {
                inter.insert(s);
            } else {
                sb.insert(s);
            }
        }
    }
    for (int s: inter) sa.erase(s);

    int x = 0;
    for (int s: sa) x += d.r[s];
    int y = 0;
    for (int s: sb) y += d.r[s];
    long long res = 1ll*x*y;
    cout << res<<"\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
