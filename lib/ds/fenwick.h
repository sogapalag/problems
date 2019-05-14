// fenwick tree, aka, Binary indexed tree.
// key trick least sig bits LSB(i) = (i&-i)
// each idx responsible [idx - LSB(i) + 1, idx]
// 1-based, [l, r] query

//~ SNIPPETS_START fenwick
template <typename T=int>
struct Fenwick {
    int n;
    vector<T> v;
    
    Fenwick(int size = 100005) : n(size+1), v(n, 0) {}
    inline void add(int p, T val) {
        for (; p <= n; p += (p&-p)) { v[p] += val; }
    }
    inline T query(int p) {
        T tmp = 0;
        for (; p > 0; p -= (p&-p)) { tmp += v[p]; }
        return tmp;
    }
    inline T query(int l, int r) {
        return query(r) - query(l-1);
    }
};
//~ SNIPPETS_END
