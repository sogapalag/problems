#include "fenwick_range_add_single_query.h"

// SNIPPETS_START fenwick_range_add_range_query
template <typename T>
struct RARQ {
    int n;
    RASQ<T> a;
    Fenwick<T> lack;

    RARQ(int _n) : n(_n), a(n), lack(n) {}

    // 0-based [l..r)
    inline void add(int l, int r, T val) {
        a.add(l+1, r+1, val);
        lack.add(l+1, val * l);
        lack.add(r+1, val * (-r));
    }
    // 0-based [0..p)
    inline T query(int p) {
        return a.query(p)*p - lack.query(p);
    }
    // 0-based [l..r)
    inline T query(int l, int r) {
        return query(r) - query(l);
    }
};
// SNIPPETS_END
