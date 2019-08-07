#include <bits/stdc++.h>

using namespace std;
// SNIPPETS_START fenwick_variant
template <typename T=int>
struct Fenwick {
    using F=function<T(T,T)>;
    int n;
    F f;
    int id;
    vector<T> v;
    
    Fenwick(int _n, F _f, T _id) : n(_n), f(_f), id(_id), v(n+1, id) {}
    inline void add(int p, T val) {
        for (; p <= n; p += (p&-p)) { v[p] = f(v[p], val); }
    }
    inline T query(int p) {
        T tmp = id;
        for (; p > 0; p -= (p&-p)) { tmp = f(tmp, v[p]); }
        return tmp;
    }
    // when f invertible, e.g. +
    inline T query(int l, int r) {
        return query(r) - query(l-1);
    }
};
// SNIPPETS_END
