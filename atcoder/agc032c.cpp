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

// iff all even, #deg>=6 > 0 || #deg=4 > 2 || #deg=4 = 2, check another circle not between AB.
// check can be done with min-cut.
// or, since we know these is another circle, we clapse all edge expect A.
// then B's circle will trigger dsu.join false.
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n+1);
    vector<int> d(n+1, 0);
    while (m--) {
        int u, v;
        cin >> u >> v;
        d[u]++; d[v]++;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    auto gg = [](){
        cout << "No" << "\n";
        exit(0);
    };
    auto wp = [](){
        cout << "Yes" << "\n";
        exit(0);
    };
    int ge6 = 0;
    int eq4 = 0;
    int A = -1;
    for (int i = 1; i <= n; i++) {
        if (d[i] & 1) gg();
        if (d[i] >= 6) ge6++;
        if (d[i] == 4) eq4++, A = i;
    }
    if (ge6) wp();
    if (eq4 >= 3) wp();
    if (eq4 <= 1) gg();
    Dsu dsu(n+1);
    for (int i = 1; i <= n; i++) {
        if (i != A) {
            for (int j: g[i]) {
                if (j != A && j < i) {
                    if (!dsu.join(i, j)) wp();
                }
            }
        }
    }
    gg();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
