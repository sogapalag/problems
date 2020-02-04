#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
// a fenwick2d impl with one dim replaced by rbtree. for space-effecience.
// Warning: plz ensure x in [1..n], while y suits Int
struct SparseCounter2d {
    using Int = int;
    using T = Tree<Int>;
    int n;
    vector<T> a;

    SparseCounter2d(int _n) : n(_n), a(n + 1) {}
    // Warning: plz ensure add/del unique
    inline void add(int x, Int y) {
        for (; x <= n; x += (x&-x)) {
            a[x].insert(y);
        }
    }
    inline void del(int x, Int y) {
        for (; x <= n; x += (x&-x)) {
            a[x].erase(y);
        }
    }
    // # 1-based <=x, <=y
    inline int query(int x, Int y) {
        int sum = 0;
        for (; x > 0; x -= (x&-x)) {
            sum += a[x].order_of_key(y + 1);
        }
        return sum;
    }
    // #1-based (,]  <=> #0-based [,)
    inline int query(int xl, Int yl, int xr, Int yr) {
        return query(xr, yr) - query(xl, yr) - (query(xr, yl) - query(xl, yl));
    }
};
