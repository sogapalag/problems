#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

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
    inline int query(int x, Int y) {
        int sum = 0;
        for (; x > 0; x -= (x&-x)) {
            sum += a[x].order_of_key(y + 1);
        }
        return sum;
    }
    inline int query(int xl, Int yl, int xr, Int yr) {
        return query(xr, yr) - query(xl, yr) - (query(xr, yl) - query(xl, yl));
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n+1), pa(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i]; pa[a[i]] = i;
    }
    vector<int> b(n+1), pb(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> b[i]; pb[b[i]] = i;
    }
    SparseCounter2d sc(n);
    for (int x = 1; x <= n; x++) {
        sc.add(pa[x], pb[x]);
    }
    while (q--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 2) {
            int x = b[l], y = b[r];
            int i = pa[x], j = pa[y];
            sc.del(i, l); sc.del(j, r);
            swap(b[l], b[r]); swap(pb[x], pb[y]);
            sc.add(i, r); sc.add(j, l);
        } else {
            int lb, rb;
            cin >> lb >> rb;
            cout << sc.query(l-1, lb-1, r, rb) << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
