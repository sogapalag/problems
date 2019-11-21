#include "fenwick.h"

// SNIPPETS_START fenwick_range_add_single_query
template <typename T>
struct RASQ {
    int n;
    Fenwick<T> diff;

    RASQ(int _n) : n(_n), diff(n) {}
    // 1-based, [l..r)
    inline void add(int l, int r, T val) {
        diff.add(l, val);
        diff.add(r, -val);
    }
    inline T query(int p) {
        return diff.query(p);
    }
};
// SNIPPETS_END
