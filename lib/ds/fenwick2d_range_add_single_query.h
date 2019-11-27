#include "fenwick2d.h"

// SNIPPETS_START fenwick2d_range_add_single_query
// if offline, use grid. no log.
template <typename T>
struct RASQ2d {
    int n, m;
    Fenwick2d<T> diff;

    RASQ2d(int _n, int _m) : n(_n), m(_m), diff(n, m) {}

    // 1-based [l..r)
    inline void add_rect(int xl, int yl, int xr, int yr, T val) {
        diff.add(xl, yl, val);
        diff.add(xl, yr, -val);
        diff.add(xr, yl, -val);
        diff.add(xr, yr, val);
    }
    // 1-based a[x][y]
    inline T query(int x, int y) {
        return diff.query(x, y);
    }
};
// SNIPPETS_END
