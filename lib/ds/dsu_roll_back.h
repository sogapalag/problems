#include <bits/stdc++.h>

using namespace std;


// SNIPPETS_START dsu_roll_back
struct Dsu {
    using pi=pair<int, int>;
    int n;
    vector<int> p;
    vector<int> r;
    vector<pi> histo;

    Dsu(int _n) { n = _n; p.resize(n); r.resize(n); init(); }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
            r[i] = 1;
        }
    }
    inline int find(int x) { // don't compress path
        while (x != p[x]) x = p[x];
        return x;
        //return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline int join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return 0;
        if (r[x] < r[y]) swap(x, y);
        histo.emplace_back(x, y);
        p[y] = x; r[x] += r[y];
        return 1;
    }
    inline int join(pi e) {
        return join(e.first, e.second);
    }
    void roll_back() {
        int x,y;
        tie(x,y) = histo.back(); histo.pop_back();
        r[x] -= r[y]; p[y] = y;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
    inline bool check(pi e) {
        return check(e.first, e.second);
    }
};
// SNIPPETS_END
