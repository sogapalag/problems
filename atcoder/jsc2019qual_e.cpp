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

struct Edge {
    int r, c, x;
    Edge() {}
    Edge(int _r, int _c, int _x) : r(_r), c(_c), x(_x) {}
    bool operator<(const Edge& _e) const {
        return x > _e.x;
    }
};

// a - r/c form a bip, greedy find match(a)
// by hall's thm, |A| <= right(A), \E m(A), so a in A, i.e. sz[u] < r[u]
void solve() {
    int n, h,w;
    cin >> n >> h >> w;
    vector<Edge> e(n);
    for (int i = 0; i < n; i++) {
        int r,c,a;
        cin >> r >> c >> a;
        r--; c += h-1;
        e[i] = {r,c,a};
    }
    Dsu d(h+w);
    sort(e.begin(), e.end());
    vector<int> sz(h+w, 0);
    long long res = 0;
    for (auto& p: e) {
        int u = d.find(p.r), v = d.find(p.c);
        // Hall's thm
        if (u == v) {
            if (sz[u] < d.r[u]){
                res += p.x;
                sz[u]++;
            }
        } else {
            if (sz[u]+sz[v] < d.r[u]+d.r[v]) {
                res += p.x;
                d.join(u,v);
                int s = sz[u]+sz[v]+1;
                sz[u] = sz[v] = s;
            }
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
