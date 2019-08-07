#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START fenwick_pmq
// prefix min/max query, 1-based, inclusive[1,p].
template <typename T=int>
struct Fenwick {
    int n;
    const T ID = 0x3f3f3f3f;
    vector<T> v;
    
    inline void comb(T& r, const T& val) {
        r = min(r, val);
    }
    Fenwick(int size = 100005) : n(size), v(n+1, ID) {}
    inline void add(int p, T val) {
        for (; p <= n; p += (p&-p)) { comb(v[p], val); }
    }
    inline T query(int p) {
        T tmp = ID;
        for (; p > 0; p -= (p&-p)) { comb(tmp, v[p]); }
        return tmp;
    }
};
// SNIPPETS_END
