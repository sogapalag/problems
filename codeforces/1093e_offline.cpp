#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
struct Fenwick {
    int n;
    vector<T> v;
    
    Fenwick(int size = 100005) : n(size), v(n+1, 0) {}
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
    int qtim;
    SparseCounter2dOffline(int _n) : n(_n), f(n), qtim(0) {}
    
    // Warning: plz add chronologically
    void add_update(X x, int y, V val) {
        evs.emplace_back(x, y, val, -1);
    }
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
            while (i < m && evs[i].x <= evs[j].x) {
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
    SparseCounter2dOffline sc(n);
    for (int x = 1; x <= n; x++) {
        sc.add_update(pa[x], pb[x], 1);
    }

    while (q--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 2) {
            int x = b[l], y = b[r];
            int i = pa[x], j = pa[y];
            sc.add_update(i, l, -1); sc.add_update(j, r, -1);
            swap(b[l], b[r]); swap(pb[x], pb[y]);
            sc.add_update(i, r, 1); sc.add_update(j, l, 1);
        } else {
            int lb, rb;
            cin >> lb >> rb;
            sc.add_query(l-1, lb-1, r, rb);
        }
    }

    sc.solve();
    for (auto& x: sc.res) {
        cout << x << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
