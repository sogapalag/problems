#include "fenwick.h"

// impl similar to partial_ord_3d. (time, x,y), contribution to which.
// Warning: ensure y in range [1..n]
// support add (x,y) +val. query rect-sum
struct SparseCounter2dOffline {
    using X = int;
    using V = int;

    int n;
    Fenwick<V> f;
    struct Event {
        X x; int y;
        V v;
        int t; // t<0 update
        Event(X _x, int _y, V _v, int _t) : x(_x), y(_y), v(_v), t(_t) {}
        bool operator<(const Event& _oth) const {
            return x < _oth.x;
        }
    };
    vector<Event> evs;
    int qtim; // track query time
    SparseCounter2dOffline(int _n) : n(_n), f(n), qtim(0) {}
    
    // Warning: plz add chronologically
    void add_update(X x, int y, V val) {
        evs.emplace_back(x, y, val, -1);
    }
    // 1-based (,] <=> 0-based [,)
    void add_query(X xl, int yl, X xr, int yr) {
        evs.emplace_back(xl, yl, +1, qtim);
        evs.emplace_back(xl, yr, -1, qtim);
        evs.emplace_back(xr, yl, -1, qtim);
        evs.emplace_back(xr, yr, +1, qtim++);
    }
    vector<V> res;
    void divi(int l, int r) {
        if (r-l <= 1) return;
        int m = (l+r)>>1;
        divi(l, m); divi(m, r);
        int i = l;
        for (int j = m; j < r; j++) {
            while (i < m && evs[i].x <= evs[j].x) { //<=, since 1-based]
                if (evs[i].t < 0) f.add(evs[i].y, evs[i].v);
                i++;
            }
            if (evs[j].t >= 0) {
                res[evs[j].t] += f.query(evs[j].y) * evs[j].v;
            }
        }
        // clear
        while (i > l) {
            if (evs[--i].t < 0) f.add(evs[i].y, -evs[i].v);
        }
        inplace_merge(evs.begin() + l, evs.begin() + m, evs.begin() + r);
    }
    void solve() {
        res.resize(qtim);
        divi(0, evs.size());
    }
};

