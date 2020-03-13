#include <bits/stdc++.h>
using namespace std;

// SNIPPETS_START dsu_r
struct Dsu {
    int n;
    vector<int> p;
    vector<int> r;
    
    Dsu(int _n) : n(_n)
        , p(n)
        , r(n)
    {
        init();
    }
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
// SNIPPETS_END
