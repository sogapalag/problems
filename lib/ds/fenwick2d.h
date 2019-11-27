#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START fenwick2d
template <typename T=int>
struct Fenwick2d {
    int n, m;
    vector<vector<T>> g;

    Fenwick2d(int _n, int _m) : n(_n), m(_m), g(n+1, vector<T>(m+1, 0)) {}
    inline void add(int x, int y, T val) {
        for (; x <= n; x += (x&-x)) {
            for (int j = y; j <= m; j += (j&-j)) {
                g[x][j] += val;
            }
        }
    }
    // 1-based [1,1..x,y] <=> 0-based [0,0..x,y)
    inline T query(int x, int y) {
        T sum = 0;
        for (; x > 0; x -= (x&-x)) {
            for (int j = y; j > 0; j -= (j&-j)) {
                sum += g[x][j];
            }
        }
        return sum;
    }
    // 1-based (l..r] <=> 0-based [l..r)
    inline T query(int xl, int yl, int xr, int yr) {
        return query(xr, yr) - query(xl, yr) - (query(xr, yl) - query(xl, yl));
    }
};
// SNIPPETS_END
